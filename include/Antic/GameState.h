#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL2/SDL.h>
#include <Antic/RenderQueue.h>

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
		void setWindow( SDL_Window* );
		/*
		virtual bool onEnter();
		virtual bool onExit();
		*/
	private:
		SDL_Window* window = nullptr;
		RenderQueue* rq = nullptr;
		//ObjectManager* om;
	};
}

#endif