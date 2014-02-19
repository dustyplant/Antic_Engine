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
		virtual void update();
		virtual void render();

		unsigned int getID();
		void setID( unsigned int newID );

		void setEntityManager( EntityManager * );
		EntityManager *getEntityManager();

	private:
		unsigned int id = 0;
		EntityManager *em = nullptr;
	};
}

#endif