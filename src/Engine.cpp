#include <Antic/Engine.h>

antic::Engine::Engine()
{
	sm = nullptr;
	window = nullptr;
	renderer = nullptr;
}

antic::Engine::~Engine()
{
	close();
}

void antic::Engine::close()
{
	if( sm != nullptr )
		delete sm;
	if( window != nullptr )
		SDL_DestroyWindow( window );
	if( renderer != nullptr )
		SDL_DestroyRenderer( renderer );
	SDL_Quit();
}

bool antic::Engine::init( std::string title, int width, int height )
{
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
		return false;

	if( window != nullptr )
	{
		printf("Error: Window already exists.\n");
		return false;
	}
	window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN );
	if( window == nullptr )
	{
		printf("Error: Window did not initialize.\n");
		return false;
	}

	if( renderer != nullptr )
	{
		printf("Error: Renderer already exists.\n");
		return false;
	}
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if( renderer == nullptr )
	{
		printf("Error: Renderer did not initialize.\n");
		return false;
	}

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
	SDL_RenderClear( renderer );
	if( sm != nullptr )
	{
		sm->render();
	}
	SDL_RenderPresent( renderer );
}

void antic::Engine::setStateManager( StateManager* newSM )
{
	if( sm != nullptr )
		delete sm;
	sm = newSM;
}