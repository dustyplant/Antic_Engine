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

GLuint antic::Entity::getID()
{
	return id;
}

void antic::Entity::setID( GLuint newID )
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