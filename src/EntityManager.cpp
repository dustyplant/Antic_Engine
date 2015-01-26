#include <Antic/EntityManager.h>
#include <iostream>

antic::EntityManager::EntityManager()
{
	currIDs = 0;
}

antic::EntityManager::~EntityManager()
{
	close();
}

bool antic::EntityManager::init()
{
	close();
	
	rq = new RenderQueue();
	if( rq->init( 7 ) == false )
		return false;

	return true;
}

void antic::EntityManager::update( float dt )
{
	for( auto iter : deletedEntities )
		removeEntityNow( iter );

	deletedEntities.clear();

	for( auto iter: entities )
		iter.second->update(dt);
}

void antic::EntityManager::render()
{
	for( auto iter: entities )
		rq->insert( iter.second );

	rq->render();
}

void antic::EntityManager::addEntity( antic::Entity* newEntity )
{
	// Will only add entity if it doesn't have an ID already assigned. Simplifies things.
	if( newEntity->getID() == 0 )
	{
		newEntity->setID( getNewID() );
		newEntity->setEntityManager( this );
		
		entities[ newEntity->getID() ] = newEntity;
	}
}

antic::Entity* antic::EntityManager::getEntity( unsigned int entityID )
{
	if( hasEntity( entityID ) )
		return entities[ entityID ];
	return nullptr;
}

bool antic::EntityManager::hasEntity( unsigned int entityID )
{
	return entities.find( entityID ) != entities.end();
}

void antic::EntityManager::removeEntity( unsigned int entityID )
{
	deletedEntities.push_back( entityID );
}

void antic::EntityManager::removeEntityNow( unsigned int entityID )
{
	if( hasEntity( entityID ) )
	{
		std::cout << "Deleting " << entityID << '\n';
		delete entities[ entityID ];
		entities.erase( entityID );

		freeIDs.push_back( entityID );
	}

}

unsigned int antic::EntityManager::getNewID()
{
	unsigned int id = 0;
	if( freeIDs.size() == 0 )
	{
		id = ++currIDs;
	}
	else
	{
		id = freeIDs.back();
		freeIDs.pop_back();
	}
	return id;
}

void antic::EntityManager::close()
{
	if( rq != nullptr )
		delete rq;

	for( auto iter: entities )
	{
		if( iter.second != nullptr )
			delete iter.second;
	}
	entities.clear();
}