#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL2/SDL.h>
#include <Antic/EntityManager.h>

namespace antic
{
	class StateManager;
	class GameState
	{
	public:
		/// Cleans everything up. Also calls close(), so you don't have to worry about it.
		GameState();
		virtual ~GameState();
		virtual bool init() = 0;
		virtual void update();
		virtual void render();

		virtual void close();

		StateManager *getStateManager();
		void setStateManager( StateManager * );

		/*
		virtual bool onEnter();
		virtual bool onExit();
		*/
		antic::EntityManager *entityManager = nullptr;

	private:
		StateManager *sm = nullptr;
	};
}

#endif