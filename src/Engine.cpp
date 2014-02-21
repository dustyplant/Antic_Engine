#include <Antic/Engine.h>
#include <Antic/SystemEvent.h>

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

bool antic::Engine::init( std::string title, int width, int height )
{
	if( AGraph::initAGraph( title, width, height ) == false )
		return false;

	return true;
}

void antic::Engine::update()
{
	antic::Subject::notifyObservers();
	if( sm != nullptr )
	{
		sm->update();
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
			push_event( sysEvent );

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