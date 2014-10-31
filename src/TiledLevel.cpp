#include <Antic/TiledLevel.h>

antic::TiledLevel::~TiledLevel()
{
	close();
}

bool antic::TiledLevel::init( std::string tmxFilePath )
{
	close();

	level = new Tmx::Map();
	level->ParseFile( tmxFilePath );
	if( level->HasError() )
	{
		printf("tmxparser Error %d: %s\n", level->GetErrorCode(), level->GetErrorText().c_str());
		close();
		return false;
	}

	for( int i = 0 ; i < level->GetNumTilesets(); ++i )
	{
		const Tmx::Tileset* tileset = level->GetTileset( i );
		std::string name = tileset->GetName();
		
		if( agraph::SpriteSheetFactory::getSS( name ) == nullptr )
		{
			std::string imagePath = tileset->GetImage()->GetSource();
			std::string imageName = imagePath.substr(0, imagePath.rfind("."));

			agraph::SpriteSheetFixed* ssf = new agraph::SpriteSheetFixed;
			ssf->generateSprites(
				agraph::TextureFactory::loadTexture( imageName, imagePath ),
				tileset->GetTileWidth(),
				tileset->GetTileHeight(),
				tileset->GetSpacing(),
				tileset->GetSpacing(),
				tileset->GetMargin(),
				tileset->GetMargin()
			);
			agraph::SpriteSheetFactory::addSS( name, ssf );
		}

		tilesets.push_back( agraph::SpriteSheetFactory::getSS( name ) );
	}

	for( int i = 0; i < level->GetNumLayers(); ++i )
	{
		const Tmx::Layer* layer = level->GetLayer( i );
		antic::TileLayer newLayer;

		for( int y = 0; y < layer->GetHeight(); ++y )
		{
			for( int x = 0; x < layer->GetWidth(); ++x )
			{
				const Tmx::MapTile& tile = layer->GetTile( x, y );
				if( tile.id != 0 )
					newLayer.addTile( tilesets[ tile.tilesetId ], x, y, tile.id);
			}
		}

		layers.push_back( newLayer );
	}

	return true;
}

void antic::TiledLevel::render()
{
	int tileWidth  = level->GetTileWidth();
	int tileHeight = level->GetTileHeight();

	for( int i = 0; i < layers.size(); ++i )
	{
		for( int j = 0; j < layers[i].tiles.size(); ++j )
		{
			antic::Tile &tile = layers[i].tiles[j];
			tile.ss->render( tile.gid, tile.x * tileWidth, tile.y * tileHeight );
		}
	}
}

void antic::TiledLevel::close()
{
	if( level != nullptr )
	{
		delete level;
		level = nullptr;
	}

	layers.clear();
}

void antic::TileLayer::addTile( agraph::SpriteSheet* ss, int x, int y, int gid )
{
	antic::Tile tile;
	tile.x   = x;
	tile.y   = y;
	tile.gid = gid;
	tile.ss  = ss;
	
	tiles.push_back( tile );
}

void antic::TileLayer::addTile( Tile tile )
{
	tiles.push_back( tile );
}

void antic::TileLayer::close()
{
	tiles.clear();
}