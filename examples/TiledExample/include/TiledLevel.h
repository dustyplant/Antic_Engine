#ifndef TILEDLEVEL_H
#define TILEDLEVEL_H

namespace antic
{
	class Tile
	{
	public:
		virtual void render();
		void setTileset( agarph::Texture* tex );
		agraph::Texture* getTileset();
	private:
		agraph::Texture* tex = nullptr;
		int gid = 0;
	};

	class Tileset
	{
	public:
		virtual void render( int gid );

		agraph::Texture *tex = nullptr;
		GLuint tileWidth;
		GLuint tileHeight;
	};

	class TiledLevel
	{
	public:
		virtual void render();

	private:
		agraph::Texture *tex = nullptr;
		std::vector< agraph::Rect > objects;		
	};
}

#endif