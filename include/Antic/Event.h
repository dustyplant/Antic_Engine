#ifndef EVENT_H
#define EVENT_H

namespace antic
{
	class Event
	{
	public:
		virtual ~Event(){};
		int getPriority(){ return priority; };

		bool operator<( Event &b ){ return getPriority() < b.getPriority(); };
		bool operator>( Event &b ){ return getPriority() > b.getPriority(); };
		bool operator==( Event &b ){ return getPriority() == b.getPriority(); };

	protected:
		int priority = 0;
	};
}

#endif