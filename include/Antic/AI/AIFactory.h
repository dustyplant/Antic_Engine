#ifndef AIFACTORY_H
#define AIFACTORY_H

#include <Antic/AI/AIState.h>
#include <Antic/ComponentAI.h>

namespace antic
{
	class AIFactory
	{
	public:	
		static ComponentAI *createGruntAI(Entity *player);
	};
}
#endif