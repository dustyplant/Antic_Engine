#include <Antic/Antic.h>
#include <Antic/Texture.h>

int main( int argc, char* argv[] )
{
	antic::Engine engine;
	if( engine.init("Example 1", 1024, 768, 60) == false )
		exit( EXIT_FAILURE );

	while( glfwWindowShouldClose( agraph::window ) == false )
	{
		glfwPollEvents();
		agraph::renderDone();
	}

	engine.close();
}