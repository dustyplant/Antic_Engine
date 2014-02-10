#ifndef ENTITY_H
#define ENTITY_H

#include <GL/glew.h>
#include <Antic/Drawable.h>

namespace antic
{
	class Entity : public Drawable
	{
	public:
		virtual ~Entity();
		virtual bool init();
		virtual void update();
		virtual void render();

		GLuint getID();
		void setID( GLuint newID );

	private:
		GLuint id = 0;
	};
}

#endif