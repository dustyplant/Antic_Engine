#ifndef ENTITYBOX_H
#define ENTITYBOX_H

#include <Antic/Entity.h>
#include <Antic/Rectangle.h>

namespace antic
{
	class EntityBox : public Entity
	{
	public:
		virtual void render();
	protected:
		Rectangel r;
	};
}

#endif