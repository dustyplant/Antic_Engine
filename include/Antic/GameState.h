#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL2/SDL.h>

namespace antic
{
	class GameState
	{
	public:
		virtual bool init() = 0;
		virtual void update() = 0;
		virtual void render() = 0;
		void setWindow( SDL_Window* );
		/*
		virtual bool onEnter();
		virtual bool onExit();
		*/
	private:
		SDL_Window* window = nullptr;
		//RenderQueue* rq;
		//ObjectManager* om;
	};
}

#endif