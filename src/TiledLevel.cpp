#include <Antic/TiledLevel.h>
#include <Antic/Physics.h>

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

	for( int i = 0; i < level->GetNumObjectGroups(); ++i )
	{
		const Tmx::ObjectGroup* objectGroup = level->GetObjectGroup( i );
		for( int j = 0; j < objectGroup->GetNumObjects(); ++j )
		{
			const Tmx::Object* tmxObj = objectGroup->GetObject( j );
			/*
			b2BodyDef groundBodyDef;
			groundBodyDef.position.Set( tmxObj->GetX() + tmxObj->GetWidth()/2.f, tmxObj->GetY() + tmxObj->GetHeight()/2.f );
			
			b2PolygonShape groundBox;
			groundBox.SetAsBox( tmxObj->GetWidth()/2.f, tmxObj->GetHeight()/2.f );

			b2Body* groundBody = antic::world->CreateBody( &groundBodyDef );
			groundBody->CreateFixture( &groundBox, 0.0f );
			*/
			antic::createBodyStatic( tmxObj->GetX(), tmxObj->GetY(), tmxObj->GetWidth(), tmxObj->GetHeight() );
		}
	}

	return true;
}

void antic::TiledLevel::render()
{
	int tileWidth  = level->GetTileWidth();
	int tileHeight = level->GetTileHeight();
	GLfloat w2 = tileWidth/2.f;
	GLfloat h2 = tileHeight/2.f;

	for( int i = 0; i < layers.size(); ++i )
	{
		for( int j = 0; j < layers[i].tiles.size(); ++j )
		{
			antic::Tile &tile = layers[i].tiles[j];
			tile.ss->render( tile.gid, tile.x * tileWidth + w2, tile.y * tileHeight + h2 );
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