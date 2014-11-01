#ifndef COMPONENTPHYSICS_H
#define COMPONENTPHYSICS_H

#include <Antic/Component.h>

namespace antic
{
	class ComponentPhysics : public Component
	{
	public:
		ComponentPhysics();
		
		virtual void update(float dt, Entity *me);
		virtual ~ComponentPhysics();

		void setVelocity( float dx, float dy);

	protected:
		float dx, dy;
	};
}

#endif