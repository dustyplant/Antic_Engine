#include <Antic/AI/AIFactory.h>
#include <Antic/AI/AIState.h>
#include <Antic/AI/Transition.h>

antic::ComponentAI* antic::AIFactory::createGruntAI(Entity *player)
{
	ComponentAI *ai = new ComponentAI();

	AIState *main = new AIState(0);
	ai->state = main;
	main->name = "main";


	AIState *pace = new AIStatePace(32);
	Transition *playerNear = new TransitionDistance(0, 4*16, player);
	playerNear->next = 1;
	main->transitions.push_back(playerNear);
	AIState *follow = new AIStateFollow(48, player);
	Transition *playerFar = new TransitionDistance(6*16, FLT_MAX, player);
	playerFar->next = 0;
	main->transitions.push_back(playerFar);

	pace->name = "pace";
	follow->name = "follow";

	main->states.push_back(pace);
	main->states.push_back(follow);
	return ai;
}