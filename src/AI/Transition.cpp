#include <Antic/AI/Transition.h>
#include <Antic/AI/AIState.h>

antic::Transition::Transition()
{
	next = -1;
}

antic::Transition::~Transition()
{
	
}

void antic::Transition::reset()
{

}

antic::TransitionHealth::TransitionHealth(int max, int min)
{
	this->max = max;
	this->min = min;
}

bool antic::TransitionHealth::test(float dt, Entity *me, AIState *state)
{
	//Entity does not yet have health information
	return false;
}

antic::TransitionDistance::TransitionDistance(float min, float max, Entity *target)
{
	this->min = min;
	this->max = max;
	this->target = target;
}

bool antic::TransitionDistance::test(float dt, Entity *me, AIState *state)
{
	float dx,dy,distance;
	dx = me->x - target->x;
	dy = me->y - target->y;
	distance = (dx*dx) + (dy*dy);
	//used squared distance to avoid sqrt
	return distance >= min*min && distance <= max*max;
}

antic::TransitionTime::TransitionTime(float time)
{
	this->cur = 0;
	this->time = time;
}

bool antic::TransitionTime::test(float dt, Entity *me, AIState *state)
{
	cur += dt;
	return cur < time;
}

void antic::TransitionTime::reset()
{
	cur = 0;
}

bool antic::TransitionSubstateDone::test(float dt, Entity *me, AIState *state)
{
	return state->isDone();
}