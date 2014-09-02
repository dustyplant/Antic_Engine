#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <Antic/GameState.h>
#include <Antic/EventSystem.h>
#include <stack>

namespace antic
{	
	class Engine;
	class StateManager : public Subject, public Observer
	{
	public:
		virtual ~StateManager();

		virtual bool init();
		virtual void update( float dt );
		virtual void render();

		// Pushes the new state onto the stack, making it the active state, and 
		// preserving the previously active state.
		void pushState( GameState* );

		// Removes and deallocates the current GameState object.
		void popState();

		// Pushes and pops safely.
		void changeState( GameState* );

		Engine *getEngine();
		void setEngine( Engine * const );

	private:
		void close();

		std::stack<GameState*> stateStack;
		Engine *engine = nullptr;

	};
}

#endif