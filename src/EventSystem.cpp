#include <Antic/EventSystem.h>

// Subject member functions
using namespace antic;

static bool compare( Event *a, Event *b )
{
	return a->getPriority() < b->getPriority();
}

Subject::Subject()
{
	std::make_heap( eventHeap.begin(), eventHeap.end(), compare );
}

Subject::~Subject()
{
	for( auto iter : observers )
		iter->removeSubject( this );

	for( auto iter : obsMap )
		for( auto iter2 : iter.second )
			iter2->removeSubject( this, iter.first );
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

void Subject::removeObserver( Observer *observer, std::type_index &t )
{
	auto iter = obsMap.find( t );
	if( iter != obsMap.end() )
		removeObserver( observer, obsMap[ t ] );	
}

void Subject::notifyObservers()
{
	while( eventHeap.size() > 0 )
	{
		Event *tempEvent = eventHeap.front();
		std::pop_heap( eventHeap.begin(), eventHeap.end(), compare );
		eventHeap.pop_back();

		for( auto iter : observers )
		{
			iter->notify( tempEvent );
		}

		std::type_index t( typeid( tempEvent ) );
		printf("%s\n", t.name());
		if( obsMap.find( t ) != obsMap.end() )
		{
			for( auto iter : obsMap[ t ] )
			{
				iter->notify( tempEvent );
			}
		}
	}
}

void Subject::push_event( Event *event )
{
	eventHeap.push_back( event );
	std::push_heap( eventHeap.begin(), eventHeap.end(), compare );
}

int Subject::getSize()
{
	return observers.size();
}

int Subject::getNumEvents()
{
	return eventHeap.size();
}

void Subject::addObserver( Observer *observer, Event *event )
{
	std::type_index t( typeid( event ) );
	auto iter = obsMap.find( t );
	if( iter != obsMap.end() )
	{
		iter->second.insert( observer );
	}
	else
	{
		obsMap[ t ];
		obsMap.at( t ).insert( observer );
	}

}
void Subject::removeObserver( Observer *observer, Event *event )
{
	std::type_index t( typeid( event ) );
	removeObserver( observer, t );
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

void Observer::notify( Event *event )
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
void Observer::addToLog( Subject *sub, Event *event )
{
	std::type_index t( typeid(event) );
	logged.insert( std::make_pair( sub, t ) );
	sub->addObserver( this, event );
}

void Observer::push_event( Event *event )
{
	eventHeap.push_back( event );
	std::push_heap( eventHeap.begin(), eventHeap.end(), compare );
}

Event* Observer::pop_event()
{
	Event *tempEvent = eventHeap.front();
	std::pop_heap( eventHeap.begin(), eventHeap.end(), compare );
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

void Observer::removeSubject( Subject *sub, Event *event )
{
	std::type_index t( typeid(event) );
	removeSubject( sub, t );
}

void Observer::removeSubject( Subject *sub, const std::type_index &t )
{
	std::pair<Subject*, std::type_index> tempPair( sub, t );

	auto iter = logged.find( tempPair );
	if( iter != logged.end() )
		logged.erase( iter );
}

int Observer::getNumSubjects()
{
	return loggedToAll.size() + logged.size();
}

bool Observer::isLogged( const std::type_index &t )
{
	bool result = false;
	for( auto iter : logged )
		if( iter.second == t )
			result = true;

	return result;
}