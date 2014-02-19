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
		virtual ~EntityManager();
		virtual bool init();
		virtual void update();
		virtual void render();

		void addEntity( Entity* );
		Entity* getEntity( unsigned int entityID );
		bool hasEntity( unsigned int entityID );
		void removeEntity( unsigned int entityID );

		//void runFunc( Functor );

	private:
		void close();

		std::map<unsigned int, Entity*> entities;

		// Number of IDs that are currently in use.
		unsigned int currIDs;

		// IDs that were used, but have since been freed.
		std::vector<unsigned int> freeIDs;

		unsigned int getNewID();

		RenderQueue *rq = nullptr;
	};
}

#endif