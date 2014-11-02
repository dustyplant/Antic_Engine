#include <Antic/ComponentPlayerInput.h>
#include <Antic/ComponentPhysics.h>
#include <Antic/SystemEvent.h>
#include <Antic/Entity.h>
#include <iostream>

float speed = 64;

antic::ComponentPlayerInput::ComponentPlayerInput()
{
	id = 2;
	upPressed = false;
	downPressed = false;
	leftPressed = false;
	rightPressed = false;
	spacePressed = false;
	leftBtnPressed = false;
	rightBtnPressed = false;
}

antic::ComponentPlayerInput::~ComponentPlayerInput()
{

}

		//sets up to listen for player input
bool antic::ComponentPlayerInput::init(Subject *s)
{
	s->addObserver(&observer);
	return true;
}
		
		//looks for any player input, updates physics component accordingly
void antic::ComponentPlayerInput::update(float dt, Entity *me)
{
	//handle input
	while(observer.getNumEvents()) {
		SystemEvent *e = dynamic_cast<SystemEvent*>( observer.pop_event() );
		if(e != nullptr) {
			//std::cout << e->event.type << ' ' << SDL_KEYDOWN << ' ' << SDL_KEYUP << '\n';
			switch(e->event.type) {
			case SDL_KEYDOWN:
				switch(e->event.key.keysym.sym) {
				case SDLK_UP:
					upPressed = true;
					break;
				case SDLK_DOWN:
					downPressed = true;
					break;
				case SDLK_RIGHT:
					rightPressed = true;
					break;
				case SDLK_LEFT:
					leftPressed = true;
					break;
				case SDLK_SPACE:
					spacePressed = true;
					break;
				}
				break;
			case SDL_KEYUP:
				switch(e->event.key.keysym.sym) {
				case SDLK_UP:
					upPressed = false;
					break;
				case SDLK_DOWN:
					downPressed = false;
					break;
				case SDLK_RIGHT:
					rightPressed = false;
					break;
				case SDLK_LEFT:
					leftPressed = false;
					break;
				case SDLK_SPACE:
					spacePressed = false;
					break;
				}
				break;
			}
		}

	}

	ComponentPhysics *p = static_cast<ComponentPhysics*>(me->getComponent(1));
	float dx=0,dy=p->dy;
	if(p != nullptr) {
		//std::cout << "Found physics component\n";
		//update motion
		// if(upPressed&&downPressed) {
		// 	dy = 0;
		// } else if(upPressed) {
		// 	dy = -speed;
		// } else if(downPressed) {
		// 	dy = speed;
		// }
		if(upPressed) {
			if(p->onGround)
				dy = -256;
		}

		if(rightPressed&&leftPressed) {
			dx = 0;
		} else if(leftPressed) {
			dx = -speed;
		} else if(rightPressed) {
			dx = speed;
		}
		p->setVelocity(dx, dy);
	}
}
