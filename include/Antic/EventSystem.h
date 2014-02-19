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
		

		void removeObserver( Observer *observer );
		void removeObserver( Observer *observer, const std::type_info *t );
		void removeObserver( Observer *observer, std::set< Observer* > &someSet );


		void notifyObservers();

		void push_event( Event event );

		int getSize();
		int getNumEvents();


		// The function definitions need to be in the header because of the templates.
		template <class T>
		void addObserver( Observer *observer )
		{
			const std::type_info *t = &typeid( T );
			auto iter = obsMap.find( t );
			if( iter != obsMap.end() )
				iter->second.insert( observer );
			else
			{
				obsMap[ t ];
				obsMap.at( t ).insert( observer );
			}
		};
		
		template <class T>
		void removeObserver( Observer *observer )
		{
			const std::type_info *t = typeid( T );
			removeObserver( observer, t );
		};
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
		

		void addToLog( Subject *sub );

		void push_event( Event event );
		Event pop_event();

		int getNumEvents();

		void removeSubject( Subject *sub );

		template <class T>
		void addToLog( Subject *sub )
		{
			logged.insert( std::make_pair( sub, &typeid(T) ) );
			sub->addObserver<T>( this );
		};
		
		template <class T>
		void removeSubject( Subject *sub )
		{
			const std::type_info *t = &typeid(T);
			std::pair<Subject*, const std::type_info *> tempPair( sub, t );

			auto iter = logged.find( tempPair );
			if( iter != logged.end() )
				logged.erase( iter );
		};

	private:
		std::vector< Event > eventHeap;
		std::set< std::pair<Subject*, const std::type_info* > > logged;
		std::set< Subject* > loggedToAll;
	};
}

#endif