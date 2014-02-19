#include <Antic/EventSystem.h>

// Subject member functions
using namespace antic;

static bool compare( Event &a, Event &b )
{
	return a.getPriority() < b.getPriority();
}

Subject::Subject()
{
	std::make_heap( eventHeap.begin(), eventHeap.end(), compare );
}

Subject::~Subject()
{

}

void Subject::addObserver( Observer *observer )
{
	observers.insert( observer );
}

void Subject::removeObserver( Observer *observer )
{
	removeObserver( observer, observers );
}

void Subject::removeObserver( Observer *observer, std::set<Observer*> &someSet )
{
	auto iter = someSet.find( observer );
	if( iter != someSet.end() )
		someSet.erase( iter );	
}

void Subject::removeObserver( Observer *observer, const std::type_info *t )
{
	auto iter = obsMap.find( t );
	if( iter != obsMap.end() )
		removeObserver( observer, obsMap[ t ] );	
}

void Subject::notifyObservers()
{
	while( eventHeap.size() > 0 )
	{
		Event tempEvent = eventHeap.front();
		std::pop_heap( eventHeap.begin(), eventHeap.end() );
		eventHeap.pop_back();

		for( auto iter : observers )
		{
			iter->notify( tempEvent );
		}

		const std::type_info *t = &typeid( &tempEvent );
		if( obsMap.find( t ) != obsMap.end() )
		{
			for( auto iter : obsMap[ t ] )
			{
				iter->notify( tempEvent );
			}
		}
	}
}

void Subject::push_event( Event event )
{
	eventHeap.push_back( event );
	std::push_heap( eventHeap.begin(), eventHeap.end() );
}

int Subject::getSize()
{
	return observers.size();
}

int Subject::getNumEvents()
{
	return eventHeap.size();
}









// Observer member functions

Observer::Observer()
{
	std::make_heap( eventHeap.begin(), eventHeap.end(), compare );
}

Observer::~Observer()
{
	removeLogs();
}

void Observer::notify( Event event )
{
	Observer::push_event( event );
}

void Observer::removeLogs()
{
	// Posibly not a safe operation.
	for( auto iter : logged )
		iter.first->removeObserver( this, iter.second );

	for( auto iter : loggedToAll )
		iter->removeObserver( this );
}

void Observer::addToLog( Subject *sub )
{
	loggedToAll.insert( sub );
	sub->addObserver( this );
}

void Observer::push_event( Event event )
{
	eventHeap.push_back( event );
	std::push_heap( eventHeap.begin(), eventHeap.end() );
}

Event Observer::pop_event()
{
	Event tempEvent = eventHeap.front();
	std::pop_heap( eventHeap.begin(), eventHeap.end() );
	eventHeap.pop_back();
	return tempEvent;
}

int Observer::getNumEvents()
{
	return eventHeap.size();
}

void Observer::removeSubject( Subject *sub )
{
	auto iter = loggedToAll.find( sub );
	if( iter != loggedToAll.end() )
		loggedToAll.erase( iter );
}