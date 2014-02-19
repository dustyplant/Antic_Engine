#include <Antic/GameState.h>

antic::GameState::GameState()
{
	entityManager = new EntityManager();
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

void antic::GameState::update()
{
	if( entityManager != nullptr )
		entityManager->update();
}

void antic::GameState::render()
{
	if( entityManager != nullptr )
		entityManager->render();
}