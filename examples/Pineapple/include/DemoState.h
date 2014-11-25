#ifndef DEMOSTATE_H
#define DEMOSTATE_H

#include <Antic/GameState.h>
#include <Antic/TiledLevel.h>

namespace antic
{
	class DemoState : public antic::GameState
	{
	public:
		DemoState();
		~DemoState();
		virtual bool init();
		virtual void update(float dt);
		virtual void render();

		bool load(char *);

	private:
		antic::TiledLevel *level;

		Entity *player;

	};
}

#endif