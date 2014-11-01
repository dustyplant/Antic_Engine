#include <Antic/GameState.h>
#include <Antic/SystemEvent.h>

antic::GameState::GameState()
{
	entityManager = new EntityManager();
	entityManager->init();
}

antic::GameState::~GameState()
{
	close();
}

void antic::GameState::close()
{
	if( entityManager != nullptr )
		delete entityManager;
	entityManager = nullptr;
}

bool antic::GameState::init()
{
	return true;
}

void antic::GameState::update( float dt )
{
	while( antic::Observer::getNumEvents() > 0 )
		antic::Subject::push_event( antic::Observer::pop_event() );

	antic::Subject::notifyObservers();

	if( entityManager != nullptr )
		entityManager->update(dt);
}

void antic::GameState::render()
{
	if( entityManager != nullptr )
		entityManager->render();
}

antic::StateManager *antic::GameState::getStateManager()
{
	return sm;	
}
void antic::GameState::setStateManager( antic::StateManager *newStateManager )
{
	/*
	if( sm != nullptr )
		//antic::Observer::removeSubject<antic::SystemEvent>( sm );
		sm->removeObserver< antic::SystemEvent >( this );
	*/
	sm = newStateManager;
	//this->addToLog<antic::SystemEvent>( sm );
}