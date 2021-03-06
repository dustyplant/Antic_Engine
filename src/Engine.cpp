#include <Antic/Engine.h>
#include <Antic/SystemEvent.h>
#include <Antic/EventSystem.h>

#include <Antic/Physics.h>

#include <iostream>
#include <math.h>

#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>

#endif

#ifdef LINUX
#endif

bool firstFrame = true;

void SleepMilliseconds( int milliseconds )
{
	#ifdef _WIN32
		Sleep( milliseconds );
	#else
		usleep( milliseconds * 1000 );
	#endif

	//#ifdef linux
	//#endif
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
	
	if( world != nullptr )
	{
		delete world;
		world = nullptr;
	}

	agraph::cleanup();
}

bool antic::Engine::init( std::string title, int width, int height, int fps, b2Vec2 gravity )
{
	close();
	
	if( agraph::initAGraph( title, width, height ) == false )
		return false;

	world = new b2World( gravity );

	lastFrame = 0;
	setFPS( fps );
	return true;
}

void antic::Engine::update()
{
	// In case of the first frame.
	if( firstFrame )
	{
		lastFrame = clock();
		firstFrame = false;
	}

	// Notify observers of events.
	antic::Subject::notifyObservers();

	// Calculate the delta time since the last frame and pass that to update.
	double thisFrame = (clock() - lastFrame) / (double)CLOCKS_PER_SEC;

	antic::world->Step( thisFrame, 8, 3 );
	if( sm != nullptr )
		sm->update( thisFrame );

	antic::clearEvents();

	// Record time of the last frame ending.
	lastFrame = clock();

	// If going fast, will sleep until time for next frame.
	if( thisFrame < this->frameTime )
		SleepMilliseconds( (int)((frameTime - thisFrame)*1000) );
		//SleepMilliseconds( 1000 );
}

void antic::Engine::gameLoop()
{
	while( glfwWindowShouldClose( agraph::window ) == false )
	{
		/*
		while( SDL_PollEvent( &this->event ) )
		{
			SystemEvent *sysEvent = new SystemEvent;
			//((SystemEvent *)sysEvent)->event = this->event;
			sysEvent->event = this->event;
			antic::Subject::push_event( sysEvent );

			if( this->event.type == SDL_QUIT )
				quit = true;
		}
		*/
		glfwPollEvents();
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
	agraph::renderDone();
}

void antic::Engine::setStateManager( StateManager* newSM )
{
	if( sm != nullptr )
		delete sm;
	
	sm = newSM;
	sm->setEngine( this );
}

antic::StateManager* antic::Engine::getStateManager()
{
	return this->sm;
}

void antic::Engine::setFPS( int fps )
{
	this->fps = fps;
	this->frameTime = 1.0 / fps;
}