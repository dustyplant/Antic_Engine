#include <Antic/ComponentAI.h>

antic::ComponentAI::ComponentAI()
{
	id = 3;
	state = nullptr;
}

antic::ComponentAI::~ComponentAI()
{
	if(state != nullptr) {
		delete state;
		state = nullptr;
	}
}
void antic::ComponentAI::update(float dt, Entity *me)
{
	if(state != nullptr) {
		state->update(dt, me);
	}
}