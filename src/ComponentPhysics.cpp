#include <Antic/Component.h>
#include <Antic/ComponentPhysics.h>
#include <Antic/Entity.h>


antic::ComponentPhysics::ComponentPhysics()
{
	id = 1;

	dx = 0;
	dy = 0;
}

antic::ComponentPhysics::~ComponentPhysics()
{

}

void antic::ComponentPhysics::update(float dt, Entity *me)
{
	me->x += dx * dt;
	me->y += dy * dt;
}

void antic::ComponentPhysics::setVelocity( float dx, float dy)
{
	this->dx = dx;
	this->dy = dy;
}