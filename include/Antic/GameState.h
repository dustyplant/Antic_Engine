#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL2/SDL.h>
#include <Antic/EntityManager.h>

namespace antic
{
	class GameState
	{
	public:
		/// Cleans everything up. Also calls close(), so you don't have to worry about it.
		GameState();
		virtual ~GameState();
		virtual bool init() = 0;
		virtual void update() = 0;
		virtual void render();

		virtual void close();

		//virtual antic::EntityManager* getEntityManager();
		//void setWindow( SDL_Window* );
		/*
		virtual bool onEnter();
		virtual bool onExit();
		*/
		antic::EntityManager *entityManager = nullptr;
	private:
		//SDL_Window* window = nullptr;
		//RenderQueue* rq = nullptr;
		//ObjectManager* om;
	};
}

#endif