#ifndef COMPONENTPLAYERINPUT_H
#define COMPONENTPLAYERINPUT_H

#include <Antic/Component.h>
#include <Antic/EventSystem.h>

namespace antic
{
	class ComponentPlayerInput : public Component
	{
	public:
		ComponentPlayerInput();

		//sets up to listen for player input
		bool init(Subject *s);
		
		//looks for any player input, updates physics component accordingly
		virtual void update(float dt, Entity *me);
		virtual ~ComponentPlayerInput();


	protected:
		Observer observer;

		bool upPressed;
		bool downPressed;
		bool leftPressed;
		bool rightPressed;
		bool spacePressed;
		bool leftBtnPressed;
		bool rightBtnPressed;
	};
}

#endif