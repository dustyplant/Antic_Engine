#include <Antic/EventSystem.h>

// Subject member functions
std::vector<antic::Event*> antic::eventsFired;

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
	auto iter = observers.begin();
	while( iter != observers.end() )
		(*(iter++))->removeSubject( this );

	for( auto iter : obsMap )
	{
		auto iter2 = iter.second.begin();
		while( iter2 != iter.second.end() )
			(*(iter2++))->removeSubject( this, iter.first );
	}
}

void Subject::addObserver( Observer *observer )
{
	// Code moved to Observer's addToLog function.
	//observers.insert( observer );
	observer->addToLog( this );
}

void Subject::addObserver( Observer *observer, Event *event )
{
	std::type_index t( typeid( *event ) );
	addObserver( observer, t );
}

void Subject::addObserver( Observer *observer, const std::type_index &t )
{
	// Code moved to Observer's addToLog function.
	/*
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
	*/
	observer->addToLog( this, t );
}

void Subject::removeObserver( Observer *observer )
{
	//removeObserver( observer, observers );
	observer->removeSubject( this );
}

void Subject::removeObserver( Observer *observer, std::set<Observer*> &someSet )
{
	auto iter = someSet.find( observer );
	if( iter != someSet.end() )
		someSet.erase( iter );	
}

void Subject::removeObserver( Observer *observer, const std::type_index &t )
{
	// Code moved to Observer's addToLog function.
	/*
	auto iter = obsMap.find( t );
	if( iter != obsMap.end() )
		removeObserver( observer, obsMap[ t ] );	
	*/
	observer->removeSubject( this, t );
}

void Subject::removeObserver( Observer *observer, Event *event )
{
	std::type_index t( typeid( *event ) );
	removeObserver( observer, t );
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

		std::type_index t( typeid( *tempEvent ) );
		if( obsMap.find( t ) != obsMap.end() )
		{
			for( auto iter : obsMap[ t ] )
			{
				iter->notify( tempEvent );

			}
		}

		// For deallocation.
		eventsFired.push_back( tempEvent );
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
	Observer::eventHeap.push_back( event );
	std::push_heap( eventHeap.begin(), eventHeap.end(), compare );
}

void Observer::removeLogs()
{
	// Posibly not a safe operation.
	auto iter = logged.begin();
	while( iter != logged.end() )
		(*(iter++)).first->removeObserver( this, (*iter).second );

	auto iter2 = loggedToAll.begin();
	while( iter2 != loggedToAll.end() )
		(*(iter2++))->removeObserver( this );
}

void Observer::addToLog( Subject *sub )
{
	loggedToAll.insert( sub );
	//sub->addObserver( this );
	// From Subject
	sub->observers.insert( this );
}
void Observer::addToLog( Subject *sub, Event *event )
{
	std::type_index t( typeid(*event) );
	addToLog( sub, t );
}

void Observer::addToLog( Subject *sub, const std::type_index &t )
{
	logged.insert( std::make_pair( sub, t ) );
	//sub->addObserver( this, t );
	// From Subject
	auto iter = sub->obsMap.find( t );
	if( iter != sub->obsMap.end() )
	{
		iter->second.insert( this );
	}
	else
	{
		sub->obsMap[ t ];
		sub->obsMap.at( t ).insert( this );
	}
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
	return Observer::eventHeap.size();
}

void Observer::removeSubject( Subject *sub )
{
	auto iter = loggedToAll.find( sub );
	if( iter != loggedToAll.end() )
	{
		loggedToAll.erase( iter );
		//sub->removeObserver( this );
		// From Subject
		sub->removeObserver( this, sub->observers );
	}
}

void Observer::removeSubject( Subject *sub, Event *event )
{
	std::type_index t( typeid(*event) );
	removeSubject( sub, t );
}

void Observer::removeSubject( Subject *sub, const std::type_index &t )
{
	std::pair<Subject*, std::type_index> tempPair( sub, t );

	auto iter = logged.find( tempPair );
	if( iter != logged.end() )
	{
		logged.erase( iter );
		//sub->removeObserver( this, t );
		// From Subject
		auto iter2 = sub->obsMap.find( t );
		if( iter2 != sub->obsMap.end() )
			sub->removeObserver( this, sub->obsMap[ t ] );
	}
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





void antic::clearEvents()
{
	std::sort( eventsFired.begin(), eventsFired.end() );
	eventsFired.erase( std::unique(eventsFired.begin(), eventsFired.end()), eventsFired.end() );
	for( int i = 0; i < eventsFired.size(); ++i )
		delete eventsFired[i];

	eventsFired.clear();
}