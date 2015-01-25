#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <Antic/Antic_Graph.h>
#include <Antic/Shader.h>

namespace antic
{

	// Vertex buffer Data for the texture.
	const GLfloat vertexData[] = {
		 0.f,  0.f, 1.0f,
		 0.f, 16.f, 1.0f,
		16.f, 16.f, 1.0f,
		16.f,  0.f, 1.0f
	};

	// Color buffer data for the texture.
	




	class Rectangle
	{
	public:
		static GLuint programID;
		static GLuint vertexBufferID;
		static GLuint colorBufferID;
		static GLfloat colorDataR[];
		static void init();
		static void cleanup();

		void render(float x1=0, float y1=0, float r=1, float g=1, float b=1);
	};

	

}

#endif