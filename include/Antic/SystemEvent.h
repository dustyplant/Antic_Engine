#ifndef SYSTEMEVENT_H
#define SYSTEMEVENT_H

#include <SDL2/SDL.h>
#include <Antic/Event.h>

namespace antic
{
	class SystemEvent : public Event
	{
	public:
		virtual ~SystemEvent(){};
		SDL_Event event;
	};
}

#endif