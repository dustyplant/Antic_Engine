#include <Antic/AI/AIState.h>
#include <cmath>
//#include <iostream>

antic::AIState::AIState(int defaultState)
{
	this->name = "";
	this->currentState = defaultState;
	this->defaultState = defaultState;
	this->done = false;
}

antic::AIState::~AIState()
{
	for(auto s : states) {
		delete s;
	}

	for(auto t : transitions) {
		delete t;
	}
}

void antic::AIState::update(float dt, Entity *me)
{
	//std::cout << name << std::endl;
	//check if this state is still active
	if(done) return;

	//update active substate
	if(currentState != -1) {
		states[currentState]->update(dt,me);
	}

	//check all transitions
	for(auto t : transitions) {
		if(t->test(dt, me, this)) {
			if(t->next == -1) {
				//next is -1, so this state is done
				currentState = -1;
				done = true;
			} else {
				//move to next substate
				currentState = t->next;
				states[currentState]->reset();
			}
			break;
		}
	}
}

bool antic::AIState::isDone() const
{
	return done;
}

void antic::AIState::reset()
{
	//set to default substate
	currentState = defaultState;
	done = false;

	//TODO: possibly reset only active substate
	//reset all substates
	for(auto s : states) {
		s->reset();
	}

	//reset all transitions
	for(auto t : transitions) {
		t->reset();
	}
}

antic::AIStatePace::AIStatePace(float dx)
{
	this->dx = dx;
}

void antic::AIStatePace::update(float dt, Entity *me)
{
	ComponentPhysics *p = static_cast<ComponentPhysics*>(me->getComponent(1));
	if(p->collision && p->dx == 0) {
		dx = -dx;
		p->dx = dx;
	}
	AIState::update(dt, me);
}

antic::AIStateFollow::AIStateFollow(float dx, Entity *target)
{
	this->dx = dx;
	this->target = target;
}

void antic::AIStateFollow::update(float dt, Entity *me)
{
	float distance = target->x - me->x;
	if(fabs(distance) > dx){
		distance = dx * (distance > 0 ? 1 : -1);
	}
	ComponentPhysics *p = static_cast<ComponentPhysics*>(me->getComponent(1));
	p->dx = distance;
	AIState::update(dt, me);
}