#include <Antic/GameState.h>

antic::GameState::GameState()
{
	//rq = new antic::RenderQueue();
	entityManager = new EntityManager();
}

antic::GameState::~GameState()
{
	close();
}
/*
void antic::GameState::setWindow( SDL_Window* win )
{
	window = win;
}
*/
void antic::GameState::close()
{
	if( entityManager != nullptr )
		delete entityManager;
	entityManager = nullptr;
}

void antic::GameState::render()
{
	if( entityManager != nullptr )
		entityManager->render();
}
/*
antic::EntityManager* antic::GameState::getEntityManager()
{
	return entityManager;
}
*/