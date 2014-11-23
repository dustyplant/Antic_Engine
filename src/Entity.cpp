#include <Antic/Entity.h>
#include <Antic/EntityManager.h>
#include <Antic/Component.h>

#include <iostream>

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

	//std::cout << "X: " << x << " Y: " << y << '\n';
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

void antic::Entity::addComponent(Component *component) 
{
	components.push_back(component);
}

///////////////
/// PEntity ///
///////////////

antic::PEntity::~PEntity()
{
	setBody( nullptr );
}

void antic::PEntity::setBody( b2Body* body )
{
	if( this->body != nullptr )
		this->body->GetWorld()->DestroyBody( this->body );
	this->body = body;
}

b2Body* antic::PEntity::getBody()
{
	return this->body;
}


///////////////
/// DEntity ///
///////////////

antic::DEntity::~DEntity()
{

}

void antic::DEntity::render()
{
	b2Fixture* fixture = this->body->GetFixtureList();
	if( fixture != nullptr )
	{
		b2Vec2 center = fixture->GetAABB( 0 ).GetCenter();
		b2Vec2 extents = fixture->GetAABB( 0 ).GetExtents();
		tex->render( center.x - extents.x, center.y - extents.y );

		//fixture->GetNext();
	}
}

void antic::DEntity::setTexture( agraph::Texture* tex )
{
	this->tex = tex;
}

agraph::Texture* antic::DEntity::getTexture()
{
	return this->tex;
}