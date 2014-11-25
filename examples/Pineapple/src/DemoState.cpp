#include "../include/DemoState.h"
#include "../include/Rectangle.h"
#include "../include/EntityBox.h"
#include <Antic/ComponentPhysics.h>
#include <Antic/ComponentPlayerInput.h>
#include <Antic/ComponentAI.h>
#include <Antic/StateManager.h>
#include <Antic/Engine.h>
#include <Antic/AI/AIFactory.h>

antic::DemoState::DemoState()
{
	level = nullptr;
}

antic::DemoState::~DemoState()
{
	if(level != nullptr)
		delete level;
}

void antic::DemoState::update(float dt) 
{

	GameState::update(dt);
}

bool antic::DemoState::init()
{
	
	return true;
}

void antic::DemoState::render()
{
	static int counter = 0;
	counter++;
	counter %= 300;
	level->render();
	Rectangle r;

	//r.render(player->x,player->y, counter/100);
	antic::GameState::render();
}

bool antic::DemoState::load(char* path)
{
	if(level != nullptr)
		delete level;
	level = new TiledLevel();
	level->init(path);
	{
		player = new EntityBox();
		ComponentPlayerInput *input = new ComponentPlayerInput();
		ComponentPhysics *physics = new ComponentPhysics();
		physics->init(level);
		physics->setGravity(256);
		input->init(static_cast<antic::Subject*>(this->getStateManager()->getEngine()));
		player->addComponent(physics);
		player->addComponent(input);

		player->x = 128;
		player->y = 128+32;
		entityManager->addEntity(player);
	}

	{
		EntityBox *enemy = new EntityBox();
		ComponentPhysics *physics = new ComponentPhysics();
		physics->init(level);
		physics->setGravity(256);
		enemy->addComponent(physics);

		ComponentAI *ai = AIFactory::createGruntAI(player);
		enemy->addComponent(ai);

		enemy->x = 256+64;
		enemy->y = 512-16;
		entityManager->addEntity(enemy);
	}
	return true;
}