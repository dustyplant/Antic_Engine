#ifndef COMPONENTPHYSICS_H
#define COMPONENTPHYSICS_H

#include <Antic/Component.h>
#include <Antic/TiledLevel.h>
#include <vector>

namespace antic
{
	struct tile {
		int x, y, id;
	};

	class ComponentPhysics : public Component
	{
	public:
		ComponentPhysics();
		
		bool init(TiledLevel *level);
		virtual void update(float dt, Entity *me);
		virtual ~ComponentPhysics();

		void setVelocity( float dx, float dy);
		void setSize( float width, float height );
		void setGravity( float gravity );
		

		bool collision = false;
		bool onGround = false;

		float dx, dy, dg;
	protected:
		float maxFallSpeed;
		float width, height;
		TiledLevel *level;
		std::vector<tile> collisionList;
	};
}

#endif