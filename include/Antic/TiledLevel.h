#ifndef TILEDLEVEL_H
#define TILEDLEVEL_H

#include <Antic/Sprite.h>
#include <Tmx.h>

namespace antic
{
	struct Tile
	{
		int x, y, gid;
		agraph::SpriteSheet* ss = nullptr;
	};

	class TileLayer
	{
	public:
		virtual void addTile( agraph::SpriteSheet* ss, int x, int y, int gid );
		virtual void addTile( Tile tile );
		virtual void close();

		std::vector< Tile > tiles;
	};

	class TiledLevel
	{
	public:
		virtual ~TiledLevel();
		virtual bool init( std::string tmxFilePath );
		virtual void render();
		virtual void close();

		
		int getTile(int x, int y, int layer_i);

	protected:
		std::vector< agraph::SpriteSheet* > tilesets;
		Tmx::Map* level = nullptr;
		std::vector< TileLayer > layers;
	};
}

#endif