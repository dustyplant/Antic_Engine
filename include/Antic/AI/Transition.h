#ifndef TRANSITION_H
#define TRANSITION_H

#include <Antic/Entity.h>
#include <Antic/ComponentPhysics.h>

namespace antic
{
	class AIState;
	/* Transitions between AIStates. When whatever condition they represent is true,
	 * the ai will move on to the next state.
	 */
	class Transition
	{
	public:
		Transition();
		virtual ~Transition();
		virtual bool test(float dt, Entity *me, AIState *state) = 0;
		virtual void reset();
		int next;
	};

	class TransitionHealth : public Transition
	{
	public: 
		TransitionHealth(int max, int min);
		virtual bool test(float dt, Entity *me, AIState *state) override;

	private:
		int max,min;
	};

	class TransitionDistance : public Transition
	{
	public:
		TransitionDistance(float min, float max, Entity *target);
		virtual bool test(float dt, Entity *me, AIState *state) override;

	private:
		float min, max;
		Entity *target;
	};

	/* waits for time to elapse. Cannot be used for long durations
	 * due to floating point errors.
	 */
	class TransitionTime : public Transition
	{
	public:
		TransitionTime(float time);
		virtual bool test(float dt, Entity *me, AIState *state) override;
		virtual void reset() override;

	private:
		float cur, time;
	};

	// class TransitionHitWall : public Transition
	// {
	// public:
	// 	TransitionHitWall(ComponentPhysics phys);
	// 	virtual bool test(float dt, Entity *me, AIState *state) override;
	// };

	class TransitionSubstateDone : public Transition
	{
	public:
		virtual bool test(float dt, Entity *me, AIState *state) override;
	};
}

#endif