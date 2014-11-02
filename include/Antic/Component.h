#ifndef COMPONENT_H
#define COMPONENT_H

namespace antic
{
	class Entity;

	class Component
	{
	public:
		virtual void update(float dt, Entity *me) = 0;
		virtual ~Component() = 0;

	protected:
		int id;

		friend class Entity;
	};
}

#endif