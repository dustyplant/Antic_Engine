#include <Antic/StateManager.h>

antic::StateManager::~StateManager()
{
	close();
}

bool antic::StateManager::init()
{
	return true;
}

void antic::StateManager::update()
{
	if( stateStack.empty() == false )
		stateStack.top()->update();
}

void antic::StateManager::render()
{
	if( stateStack.empty() == false )
		stateStack.top()->render();	
}

void antic::StateManager::pushState( GameState* newState )
{
	stateStack.push( newState );
}

void antic::StateManager::popState()
{
	if( stateStack.size() > 0 )
		stateStack.pop();
}

void antic::StateManager::changeState( GameState* newState )
{
	if( stateStack.size() > 0 )
		stateStack.pop();

	stateStack.push( newState );
}

void antic::StateManager::setWindow( SDL_Window* win )
{
	window = win;
}

void antic::StateManager::close()
{
	while( stateStack.size() > 0 )
	{
		delete stateStack.top();
		stateStack.pop();
	}
}