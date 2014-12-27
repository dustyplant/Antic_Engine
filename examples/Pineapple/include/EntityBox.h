#ifndef ENTITYBOX_H
#define ENTITYBOX_H

#include <Antic/Entity.h>
#include "Rectangle.h"

namespace antic
{
	class EntityBox : public Entity
	{
	public:
		int player = 0;
		virtual void render();
	protected:
		Rectangle r;
	};
}

#endif