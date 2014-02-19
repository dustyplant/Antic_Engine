#ifndef EVENTSYSTEM_H
#define EVENTSYSTEM_H

#include <vector>
#include <map>
#include <set>
#include <typeinfo>
#include <typeindex>
#include <Antic/Event.h>
#include <algorithm>

namespace antic
{
	class Observer;

	class Subject
	{
	public:
		Subject();
		virtual ~Subject();

		void addObserver( Observer *observer );
		
		
		void removeObserver( Observer *observer );
		void removeObserver( Observer *observer, std::type_index &t );
		void removeObserver( Observer *observer, std::set< Observer* > &someSet );


		void notifyObservers();

		void push_event( Event *event );

		int getSize();
		int getNumEvents();

		void addObserver( Observer *observer, Event *event );
		void removeObserver( Observer *observer, Event *event );

	private:
		std::set< Observer* > observers;
		std::map< std::type_index, std::set<Observer*> >obsMap;

		std::vector< Event* > eventHeap;
	};



	class Observer
	{
	public:
		Observer();
		virtual ~Observer();

		virtual void notify( Event *event );

		void removeLogs();
		

		void addToLog( Subject *sub );

		void push_event( Event *event );
		Event* pop_event();

		int getNumEvents();

		void removeSubject( Subject *sub );

		void addToLog( Subject *sub, Event *event );
		void removeSubject( Subject *sub, Event *event );

	private:
		std::vector< Event* > eventHeap;
		std::set< std::pair<Subject*, std::type_index > > logged;
		std::set< Subject* > loggedToAll;
	};
}

#endif