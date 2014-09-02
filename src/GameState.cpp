#include <Antic/GameState.h>

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

void antic::GameState::update( float dt )
{
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
	sm = newStateManager;
}