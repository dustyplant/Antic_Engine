#include "../include/EntityBox.h"
#include <Antic/ComponentPhysics.h>

void antic::EntityBox::render()
{

	int c = 1;
	ComponentPhysics *p = static_cast<ComponentPhysics*> (getComponent(1));
	if(p != nullptr) {
		if(p->collision) {
			c = 2;
		}
	}
	c = player;
	r.render(x,y,c);
}