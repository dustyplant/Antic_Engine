#include <Antic/Entity.h>
#include <Antic/EntityManager.h>
#include <Antic/Antic_Graph.h>

antic::Entity::~Entity()
{

}

bool antic::Entity::init()
{
	return true;
}

void antic::Entity::update( float dt )
{

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
		agraph::pushMatrix();
			agraph::translate( center.x, center.y );
			agraph::rotate2D( this->body->GetAngle() );
			tex->render();
		agraph::popMatrix();

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