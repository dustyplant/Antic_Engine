#ifndef AISTATE_H
#define AISTATE_H

#include <vector>
#include <string>
#include <Antic/AI/Transition.h>

using std::vector;
using std::string;

namespace antic
{
	class Entity;
	class AIFactory;

	class AIState
	{
	public:
		AIState(int defaultState = -1);
		virtual ~AIState();
		virtual void update(float dt, Entity *me);
		bool isDone() const;
		virtual void reset(Entity *me);
		//returns the name of this state and active substates
		string getName();

		string name;

	protected:
		int currentState, defaultState;
		bool done;
		vector<AIState*> states;
		vector<Transition*> transitions;

		friend AIFactory;
	};

	class AIStatePace : public AIState
	{
	public:
		AIStatePace(float dx);
		virtual void update(float dt, Entity *me) override;
		virtual void reset(Entity *me);
		
	protected:
		//TODO: move this info somewhere else
		float dx;
	};

	class AIStateJump : public AIState
	{
	public:
		AIStateJump(float dy);
		virtual void update(float dt, Entity *me) override;
		
	protected:
		//TODO: move this info somewhere else
		float dy;
	};

	class AIStateFollow : public AIState
	{
	public:
		AIStateFollow(float dx, Entity *target);
		virtual void update(float dt, Entity *me) override;
		
	protected:
		//TODO: move this info somewhere else
		float dx;
		Entity *target;
	};
}

#endif