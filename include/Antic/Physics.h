#ifndef PHYSICS_H
#define PHYSICS_H

#include <Box2D/Box2D.h>

namespace antic
{
	extern b2World* world;
	b2Body* createBodyStatic(  float x, float y, float w, float h );
	b2Body* createBodyDynamic( float x, float y, float w, float h, float density, float friction );
}

#endif