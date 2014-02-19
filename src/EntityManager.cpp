#include <Antic/EntityManager.h>

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

void antic::EntityManager::update()
{
	for( auto iter: entities )
		iter.second->update();
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
	if( hasEntity( entityID ) )
	{
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