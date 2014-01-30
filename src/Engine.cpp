#include <Antic/Engine.h>

antic::Engine::Engine()
{
	sm = nullptr;
	window = nullptr;
	context = nullptr;
	//renderer = nullptr;
}

antic::Engine::~Engine()
{
	SDL_GL_DeleteContext( context );
	close();
}

void antic::Engine::close()
{
	if( sm != nullptr )
		delete sm;
	if( window != nullptr )
		SDL_DestroyWindow( window );
	/*
	if( renderer != nullptr )
		SDL_DestroyRenderer( renderer );
	*/
	SDL_Quit();
}

bool antic::Engine::init( std::string title, int width, int height )
{
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
	context = SDL_GL_CreateContext( window );
	/*
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
	*/

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	/*
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0, width, height, 0, 1, -1 );
	glViewport( 0, 0, width, height );
	glMatrixMode( GL_MODELVIEW );
	*/
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

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
	/*
	SDL_RenderClear( renderer );
	if( sm != nullptr )
	{
		sm->render();
	}
	SDL_RenderPresent( renderer );
	*/

	SDL_GL_SwapWindow( window );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
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
SDL_Renderer* antic::Engine::getRenderer()
{
	return renderer;
}
*/