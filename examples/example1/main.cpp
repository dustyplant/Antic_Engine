#include <Antic/Antic.h>
#include <Antic/Texture.h>

int main( int argc, char* argv[] )
{
	antic::Engine engine;
	if( engine.init("Example 1", 1024, 768, 60) == false )
		exit( EXIT_FAILURE );

	bool quit = false;
	while( quit == false )
	{
		while( SDL_PollEvent( &engine.event ) )
			if( engine.event.type == SDL_QUIT )
				quit = true;

		agraph::renderDone();
	}

	engine.close();
}