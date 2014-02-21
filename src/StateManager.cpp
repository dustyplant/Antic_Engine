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
	printf("Event Heap Size Before: %d\n", antic::Subject::getNumEvents());
	antic::Subject::notifyObservers();
	printf("Event Heap Size After: %d\n", antic::Subject::getNumEvents());

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
	newState->setStateManager( this );
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

void antic::StateManager::close()
{
	while( stateStack.size() > 0 )
	{
		delete stateStack.top();
		stateStack.pop();
	}
}

antic::Engine *antic::StateManager::getEngine()
{
	return engine;
}

void antic::StateManager::setEngine( antic::Engine *newEngine )
{
	engine = newEngine;
}