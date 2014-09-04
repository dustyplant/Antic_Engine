#include <Antic/Engine.h>
#include <Antic/SystemEvent.h>

#include <iostream>
#include <math.h>

#ifdef _WIN32
	#include <windows.h>
#endif

#ifdef LINUX
	#include <unistd.h>
#endif

bool firstFrame = true;

void SleepMilliseconds( int milliseconds )
{
	#ifdef _WIN32
		Sleep( milliseconds );
	#endif

	#ifdef linux
		usleep( milliseconds * 1000 );
	#endif
}

antic::Engine::Engine()
{
	sm = nullptr;
}

antic::Engine::~Engine()
{
	close();
}

void antic::Engine::close()
{
	if( sm != nullptr )
		delete sm;
	sm = nullptr;
	
	AGraph::cleanup();
}

bool antic::Engine::init( std::string title, int width, int height, int fps )
{
	if( AGraph::initAGraph( title, width, height ) == false )
		return false;

	lastFrame = 0;
	setFPS( fps );
	return true;
}

void antic::Engine::update()
{
	// In case of the first frame.
	if( firstFrame ){
		lastFrame = clock();
		firstFrame = false;
	}

	// Notify observers of events.
	antic::Subject::notifyObservers();

	// Calculate the delta time since the last frame and pass that to update.
	double thisFrame = (clock() - lastFrame) / (double)CLOCKS_PER_SEC;
	if( sm != nullptr )
		sm->update( thisFrame );

	// Record time of the last frame ending.
	lastFrame = clock();

	// If going fast, will sleep until time for next frame.
	if( thisFrame < this->frameTime ){
		SleepMilliseconds( (int)((frameTime - thisFrame)*1000) );		
	}
}

void antic::Engine::gameLoop()
{
	bool quit = false;
	while( quit == false )
	{
		while( SDL_PollEvent( &this->event ) )
		{
			SystemEvent *sysEvent = new SystemEvent;
			//((SystemEvent *)sysEvent)->event = this->event;
			sysEvent->event = this->event;
			antic::Subject::push_event( sysEvent );

			if( this->event.type == SDL_QUIT )
				quit = true;
		}
		update();
		render();
	}
}

void antic::Engine::render()
{
	if( sm != nullptr )
	{
		sm->render();
	}
	AGraph::renderDone();
}

void antic::Engine::setStateManager( StateManager* newSM )
{
	if( sm != nullptr )
		delete sm;
	sm = newSM;
	sm->setEngine( this );
}

void antic::Engine::setFPS( int fps )
{
	this->fps = fps;
	this->frameTime = 1.0 / fps;
}