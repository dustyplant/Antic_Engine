#ifndef ANTIC_MAIN_H
#define ANTIC_MAIN_H

#include <Antic/StateManager.h>
#include <Antic/Antic_Graph.h>
#include <Antic/EventSystem.h>

//#include <Antic/Services.h>

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstdio>
/*
#include <ctime>
#include <chrono>
#include <thread>
*/
#include <time.h>

/**
 * @brief NameSpace of the Antic_Engine
 */
namespace antic
{
	/**
	 * @brief The core of the game engine.
	 * @details The core of the game engine. Start by instantiating an Engine object.
	 * 			Make sure to initialize the object by running its init() function.
	 * 			Next, either choose to create your own game loop, or run the default game loop
	 * 			with the gameLoop() function.
	 */
	class Engine : public Subject
	{
	public:
		Engine();

		/// Cleans everything up. Also calls close(), so you don't have to worry about it.
		virtual ~Engine();

		/**
		 * @brief Initialization function. Always call this before you start using the engine.
		 * @details Call this before doing anything else with the engine. This function also initializes the window and SDL2.
		 * 
		 * @param title This will be the title of the window.
		 * @param width The width of the window.
		 * @param height The height of the window.
		 * @return True if everything went fine, false if not.
		 */
		virtual bool init( std::string title, int width, int height, int fps = -1 );

		/**
		 * @brief Updates the engine.
		 * @details This will update the StateManager.
		 */
		virtual void update();

		/**
		 * @brief Renders to the screen.
		 * @details Calls the StateManager's render function. This also handles swapping and clearing the render buffer.
		 */
		virtual void render();

		/**
		 * @brief This is a simple game loop that is usually just copypasta code.
		 * @details This is a convenience function that will handle the window closing, passing system events, updating, and rendering.
		 */
		virtual void gameLoop();

		/**
		 * @brief Destroyes the engine.
		 * @details You don't need to call this because the destructor will call this. It'll also close SDL2, deleting all loaded textures and such. Only call this if you are going to init() the engine again.
		 */
		void close();

		/**
		 * @brief Set the Game State Manager
		 * @details This is important to call. The engine will run without the StateManager being set, but you typically want this to be set to something or else nothing will be happening. Make sure to add at least one GameState to the StateManager.
		 * 
		 * @param r A pointer to the StateManager object that you are passing in. It will be destroyed by the engine.
		 */
		void setStateManager( StateManager* );

		/**
		 * @brief Set max fps.
		 * @param fps This is the fps to set the max to.
		 */
		void setFPS( int fps );

		/**
		 * You can pass SDL events here.
		 */
		SDL_Event event;
	private:

		/**
		 * The StateManager that the engine will be updating and rendering.
		 */
		StateManager* sm;

		/**
		 * This is to calculate the delta time.
		 */
		//std::chrono::time_point<std::chrono::system_clock> lastFrame;
		clock_t lastFrame;

		/**
		 * This determines the frames per second. -1 means that there will be no limit.
		 */
		int fps;

		/**
		 * This is to keep track of how long a frame is.
		 */
		double frameTime;
	};
}

#endif