#include "../include/EntityBox.h"
#include <Antic/ComponentPhysics.h>
#include <Antic/ComponentAI.h>
#include <iostream>

antic::EntityBox::EntityBox() {
	r = 0;
	g = 1;
	b = 0;
}

void antic::EntityBox::update( float dt) {
	ComponentAI *ai = static_cast<ComponentAI*>(this->getComponent(3));
	if(ai != nullptr) {
		
		if(ai->getStateName() == "main:follow") {
			r=1;
			g=0;
			b=1;
		} else
		if(ai->getStateName() == "main:pace") {
			r=0;
			g=0;
			b=1;
		} else {
			std::cout << ai->getStateName() << '\n';
		}
		
	}
	Entity::update(dt);
}

void antic::EntityBox::render()
{
	rect.render(x,y,r,g,b);
}