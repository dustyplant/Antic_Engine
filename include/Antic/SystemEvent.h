#ifndef SYSTEMEVENT_H
#define SYSTEMEVENT_H

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