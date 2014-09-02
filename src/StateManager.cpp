#include <Antic/StateManager.h>

antic::StateManager::~StateManager()
{
	close();
}

bool antic::StateManager::init()
{
	return true;
}

void antic::StateManager::update( float dt )
{
	// Passing events from the observer event heap to the subject event heap.
	while( antic::Observer::getNumEvents() > 0 )
		antic::Subject::push_event( antic::Observer::pop_event() );

	// Passing events from the subject event heap to all logged observers.
	antic::Subject::notifyObservers();

	// Updates the active GameState object.
	if( stateStack.empty() == false )
		stateStack.top()->update(dt);
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