#ifndef COMPONENTAI_H
#define COMPONENTAI_H

#include <Antic/Component.h>
#include <Antic/AI/AIState.h>

namespace antic
{
	class AIFactory;

	class ComponentAI : public Component
	{
	public:
		ComponentAI();
		virtual void update(float dt, Entity *me);
		virtual ~ComponentAI();

	protected:
		AIState *state;

		friend AIFactory;
	};
}

#endif