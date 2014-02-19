#include <Antic/Entity.h>
#include <Antic/EntityManager.h>

antic::Entity::~Entity()
{

}

bool antic::Entity::init()
{
	return true;
}

void antic::Entity::update()
{

}

void antic::Entity::render()
{

}

unsigned int antic::Entity::getID()
{
	return id;
}

void antic::Entity::setID( unsigned int newID )
{
	id = newID;
}


void antic::Entity::setEntityManager( antic::EntityManager *entityManager )
{
	em = entityManager;
}

antic::EntityManager *antic::Entity::getEntityManager()
{
	return em;
}