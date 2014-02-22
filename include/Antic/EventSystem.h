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
		void addObserver( Observer *observer, Event *event );
		void addObserver( Observer *observer, const std::type_index &t );
		
		
		void removeObserver( Observer *observer );
		void removeObserver( Observer *observer, const std::type_index &t );
		void removeObserver( Observer *observer, Event *event );



		void notifyObservers();

		void push_event( Event *event );

		int getSize();
		int getNumEvents();

		template <class T>
		void addObserver( Observer *observer )
		{
			T *event = new T;
			std::type_index t( typeid(*event) );
			delete event;
			addObserver( observer, t );
		};

		template <class T>
		void removeObserver( Observer *observer )
		{
			T *event = new T;
			std::type_index t( typeid(*event) );
			delete event;
			removeObserver( observer, t );
		};

	private:
		std::set< Observer* > observers;
		std::map< std::type_index, std::set<Observer*> >obsMap;

		std::vector< Event* > eventHeap;
		
		// A friend class to reduce code between the two classes.
		friend class Observer;

		void removeObserver( Observer *observer, std::set< Observer* > &someSet );
	};



	class Observer
	{
	public:
		Observer();
		virtual ~Observer();

		virtual void notify( Event *event );

		void removeLogs();
		

		void addToLog( Subject *sub );
		void addToLog( Subject *sub, Event *event );
		void addToLog( Subject *sub, const std::type_index &t );

		Event* pop_event();


		void removeSubject( Subject *sub );

		void removeSubject( Subject *sub, Event *event );
		void removeSubject( Subject *sub, const std::type_index &t );
		
		int getNumEvents();
		int getNumSubjects();
		bool isLogged( const std::type_index &t );

		template <class T>
		void addToLog( Subject *sub )
		{
			T *event = new T;
			std::type_index t( typeid(*event) );
			delete event;
			addToLog( sub, t );
		};

		template <class T>
		void removeSubject( Subject *sub )
		{
			T *event = new T;
			std::type_index t( typeid(*event) );
			delete event;
			removeSubject( sub, t );
		};

	private:
		std::vector< Event* > eventHeap;
		std::set< std::pair<Subject*, std::type_index > > logged;
		std::set< Subject* > loggedToAll;
	};
}

#endif