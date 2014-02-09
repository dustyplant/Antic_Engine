#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <Antic/GameState.h>
#include <stack>
#include <SDL2/SDL.h>

namespace antic
{	
	class StateManager
	{
	public:
		virtual ~StateManager();

		virtual bool init();
		virtual void update();
		virtual void render();

		// Pushes the new state onto the stack, making it the active state, and 
		// preserving the previously active state.
		void pushState( GameState* );

		// Removes and deallocates the current GameState object.
		void popState();

		// Pushes and pops safely.
		void changeState( GameState* );

		void setWindow( SDL_Window* );
	private:
		void close();
		std::stack<GameState*> stateStack;
		SDL_Window* window;
	};
}

#endif