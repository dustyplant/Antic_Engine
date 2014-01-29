#ifndef GAMESTATE_H
#define GAMESTATE_H

namespace antic
{
	class GameState
	{
	public:
		virtual bool init() = 0;
		virtual void update() = 0;
		virtual void render() = 0;
		/*
		virtual bool onEnter();
		virtual bool onExit();
		*/
	private:
		//RenderQueue* rq;
		//ObjectManager* om;
	};
}

#endif