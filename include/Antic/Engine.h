#ifndef ANTIC_MAIN_H
#define ANTIC_MAIN_H

#include <Antic/StateManager.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

namespace antic
{
	class Engine
	{
	public:
		Engine();
		virtual ~Engine();
		virtual bool init( std::string title, int width, int height );
		virtual void update();
		virtual void render();

		void close();

		void setStateManager( StateManager* );

		SDL_Event event;
	private:
		StateManager* sm;
		SDL_Window* window;
		SDL_Renderer* renderer;
	};
}

#endif