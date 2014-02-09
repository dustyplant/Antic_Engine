#include <Antic/Engine.h>

antic::Engine::Engine()
{
	sm = nullptr;
	window = nullptr;
	context = nullptr;
}

antic::Engine::~Engine()
{
	//glDeleteProgram( programID );
	//SDL_GL_DeleteContext( context );
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
	/*
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
		return false;

	if( window != nullptr )
	{
		printf("Error: Window already exists.\n");
		close();
		return false;
	}
	window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );
	if( window == nullptr )
	{
		printf("Error: Window did not initialize.\n");
		close();
		return false;
	}
	*/

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
	//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
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
}

SDL_Window* antic::Engine::getWindow()
{
	return window;
}
/*
antic::Services & antic::Engine::getServices()
{
	return services;
}
*/