#include <Antic/GameState.h>

antic::GameState::GameState()
{
	rq = new antic::RenderQueue();
}

antic::GameState::~GameState()
{
	close();
}

void antic::GameState::setWindow( SDL_Window* win )
{
	window = win;
}

void antic::GameState::close()
{
	if( rq != nullptr )
		delete rq;
	rq = nullptr;
}

void antic::GameState::render()
{
	if( rq != nullptr )
		rq->render();
}