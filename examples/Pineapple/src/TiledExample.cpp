#include <Antic/Antic.h>
#include <Antic/TiledLevel.h>
#include "../include/DemoState.h"
#include "../include/Rectangle.h"

int main( int argc, char* argv[] )
{
	antic::Engine engine;
	if( engine.init("Pineapple", 1024, 768) == false )
		exit( EXIT_FAILURE );

	antic::StateManager *stateManager = new antic::StateManager();
	stateManager->init();
	engine.setStateManager(stateManager);

	antic::DemoState *demoState = new antic::DemoState();
	demoState->setStateManager(stateManager);
	demoState->load("res/Test2.tmx");
	demoState->init();

	stateManager->changeState(demoState);

	antic::Rectangle::init();

	// antic::TiledLevel level;
	// if( level.init("res/Test2.tmx") == false )
	// 	exit( EXIT_FAILURE );

	bool quit = false;

	engine.gameLoop();
	// while( quit == false )
	// {
	// 	while( SDL_PollEvent( &engine.event ) )
	// 		if( engine.event.type == SDL_QUIT )
	// 			quit = true;

	// 	//level.render();
	// 	engine.gameLoop();
	// 	//agraph::renderDone();
	// }
	antic::Rectangle::cleanup();
	engine.close();
}