#ifndef ENTITY_H
#define ENTITY_H

#include <Antic/Drawable.h>
#include <vector>

using std::vector;
#include <Antic/Texture.h>
#include <Antic/Physics.h>

namespace antic
{
	class EntityManager;
	class Component;
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

		Component* getComponent(int id);
		void addComponent(Component *component);

		float x,y;
	protected:
		unsigned int id = 0;
		EntityManager *em = nullptr;


		vector<Component*> components;
	};

	// Physics Entity
	class PEntity: public Entity
	{
	public:
		virtual ~PEntity();
		virtual void setBody( b2Body* body );
		virtual b2Body* getBody();

	protected:
		b2Body* body = nullptr;
	};

	// Drawing Entity
	class DEntity: public PEntity
	{
	public:
		virtual ~DEntity();
		virtual void render();
		virtual void setTexture( agraph::Texture* tex );
		virtual agraph::Texture* getTexture();

	protected:
		agraph::Texture* tex = nullptr;
	};
}

#endif