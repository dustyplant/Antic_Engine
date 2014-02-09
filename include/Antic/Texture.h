#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <Antic/Drawable.h>
#include <Antic/Services.h>

namespace antic
{
	class Texture : public antic::Drawable
	{
	public:
		Texture( antic::Services *services );
		virtual ~Texture();

		virtual bool loadImage( std::string path );
		virtual void render();

		GLuint getWidth();
		GLuint getHeight();
		std::string getPath();
		GLuint getTexID();

		glm::vec2 position;

	private:
		GLuint textureID;
		GLuint vertexArrayID;
		GLuint vertexBufferID;
		GLuint uvBufferID;

		GLuint width;
		GLuint height;
		std::string path;

		antic::Services *services;
		GLuint textureSamplerID;

		void close();
		void genBuffers();
	};
}

#endif