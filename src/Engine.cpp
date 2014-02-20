#include <Antic/Engine.h>

antic::Engine::Engine()
{
	sm = nullptr;
	window = nullptr;
	context = nullptr;
}

antic::Engine::~Engine()
{
	close();
}

void antic::Engine::close()
{
	if( sm != nullptr )
		delete sm;
	sm = nullptr;

	if( window != nullptr )
		SDL_DestroyWindow( window );
	window = nullptr;
	
	SDL_Quit();
}

bool antic::Engine::init( std::string title, int width, int height )
{
	if( AGraph::initAGraph( title, width, height ) == false )
		return false;

	return true;
}

void antic::Engine::update()
{
	if( sm != nullptr )
	{
		sm->update();
	}
}

void antic::Engine::render()
{
	if( sm != nullptr )
	{
		sm->render();
	}
	AGraph::renderDone();
}

void antic::Engine::setStateManager( StateManager* newSM )
{
	if( sm != nullptr )
		delete sm;
	sm = newSM;
	sm->setEngine( this );
}

SDL_Window* antic::Engine::getWindow()
{
	return window;
}