#ifndef EVENTSYSTEM_H
#define EVENTSYSTEM_H

#include <vector>
#include <map>
#include <set>
#include <typeinfo>
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
		
		template <class T>
		void addObserver( Observer *observer );

		void removeObserver( Observer *observer );
		void removeObserver( Observer *observer, const std::type_info *t );
		void removeObserver( Observer *observer, std::set< Observer* > &someSet );

		template <class T>
		void removeObserver( Observer *observer );

		void notifyObservers();

		void push_event( Event event );

		int getSize();
		int getNumEvents();

	private:
		std::set< Observer* > observers;
		std::map< const std::type_info*, std::set<Observer*> >obsMap;

		std::vector< Event > eventHeap;
	};



	class Observer
	{
	public:
		Observer();
		virtual ~Observer();

		virtual void notify( Event event );

		void removeLogs();
		
		template <class T>
		void addToLog( Subject &sub );

		void addToLog( Subject &sub );

		void push_event( Event event );
		Event pop_event();

		int getNumEvents();

		void removeSubject( Subject *sub );

		template <class T>
		void removeSubject( Subject *sub );

	private:
		std::vector< Event > eventHeap;
		std::set< std::pair<Subject*, const std::type_info* > > logged;
		std::set< Subject* > loggedToAll;
	};
}

#endif