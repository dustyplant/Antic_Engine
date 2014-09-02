#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <Antic/Entity.h>
#include <Antic/RenderQueue.h>
#include <map>
#include <vector>

namespace antic
{
	class EntityManager
	{
	public:
		EntityManager();
		virtual ~EntityManager();
		virtual bool init();
		virtual void update( float dt );
		virtual void render();

		virtual void addEntity( Entity* );
		virtual Entity* getEntity( unsigned int entityID );
		virtual bool hasEntity( unsigned int entityID );
		virtual void removeEntity( unsigned int entityID );

		//void runFunc( Functor );

	protected:
		void close();

		std::map<unsigned int, Entity*> entities;
		
	private:
		std::vector<unsigned int> deletedEntities;
		void removeEntityNow( unsigned int entityID );

		// Number of IDs that are currently in use.
		unsigned int currIDs;

		// IDs that were used, but have since been freed.
		std::vector<unsigned int> freeIDs;

		// Starts at 1, so there will never be an id of 0.
		unsigned int getNewID();

		RenderQueue *rq = nullptr;
	};
}

#endif