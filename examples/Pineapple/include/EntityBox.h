#ifndef ENTITYBOX_H
#define ENTITYBOX_H

#include <Antic/Entity.h>
#include "Rectangle.h"

namespace antic
{
	class EntityBox : public Entity
	{
	public:
		EntityBox();
		virtual void update( float dt) override;
		virtual void render() override;
		float r,g,b;
	protected:
		Rectangle rect;
	};
}

#endif