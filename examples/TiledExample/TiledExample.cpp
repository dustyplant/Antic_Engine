#include <Antic/Antic.h>
#include <Antic/TiledLevel.h>

int main( int argc, char* argv[] )
{
	antic::Engine engine;
	if( engine.init("TiledExample", 1024, 768) == false )
		exit( EXIT_FAILURE );

	antic::TiledLevel level;
	if( level.init("res/Test1.tmx") == false )
		exit( EXIT_FAILURE );

	bool quit = false;
	while( quit == false )
	{
		while( SDL_PollEvent( &engine.event ) )
			if( engine.event.type == SDL_QUIT )
				quit = true;

		level.render();
		agraph::renderDone();
	}

	engine.close();
}