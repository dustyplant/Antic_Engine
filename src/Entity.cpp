#include <Antic/Entity.h>
#include <Antic/EntityManager.h>
#include <Antic/Component.h>

antic::Entity::~Entity()
{
	for(auto it = components.begin(); it != components.end(); ++it) {
		delete (*it);
	}
}

bool antic::Entity::init()
{
	return true;
}

void antic::Entity::update( float dt )
{
	for(auto it = components.begin(); it != components.end(); ++it) {
		(*it)->update(dt,this);
	}
}

void antic::Entity::render()
{

}

void antic::Entity::kill()
{
	if( this->em != nullptr )
		this->em->removeEntity( getID() );
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

antic::Component *antic::Entity::getComponent(int id) 
{
	for(auto it = components.begin(); it != components.end(); ++it) {
		if((*it)->id == id)
		{
			return *it;
		}
	}
	return nullptr;
}