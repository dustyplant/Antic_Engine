#include <Antic/Engine.h>
#include <Antic/SystemEvent.h>
//#include <unistd.h>

#include <iostream>
#include <math.h>

bool firstFrame = true;

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

	lastFrame = std::chrono::high_resolution_clock::now();
	setFPS( fps );
	return true;
}

void antic::Engine::update()
{
	// In case of the first frame.
	if( firstFrame ){
		lastFrame = std::chrono::high_resolution_clock::now();
		firstFrame = false;
	}
	// Notify observers of events.
	antic::Subject::notifyObservers();


	// Calculate the delta time since the last frame and pass that to update.
	std::chrono::duration<double> thisFrame = std::chrono::high_resolution_clock::now() - lastFrame;
	if( sm != nullptr )
		sm->update( thisFrame.count() ); 

	// Record time of the last frame ending.
	lastFrame = std::chrono::high_resolution_clock::now();

	// If going fast, will sleep until time for next frame.
	if( thisFrame.count() < this->frameTime )
		std::this_thread::sleep_for( std::chrono::milliseconds( (int)((this->frameTime - thisFrame.count()) * 1000) ) );
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