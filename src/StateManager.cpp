#include <Antic/StateManager.h>

antic::StateManager::~StateManager()
{
	while( stateStack.size() > 0 )
	{
		delete stateStack.top();
		stateStack.pop();
	}
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