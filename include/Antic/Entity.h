#ifndef ENTITY_H
#define ENTITY_H

#include <Antic/Drawable.h>

namespace antic
{
	class EntityManager;
	class Entity : public Drawable
	{
	public:
		virtual ~Entity();
		virtual bool init();
		virtual void update( float dt );
		virtual void render();

		virtual void kill();

		unsigned int getID();
		void setID( unsigned int newID );

		void setEntityManager( EntityManager * );
		EntityManager *getEntityManager();

	protected:
		unsigned int id = 0;
		EntityManager *em = nullptr;
	};
}

#endif