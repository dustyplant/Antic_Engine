#include <Antic/Entity.h>

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