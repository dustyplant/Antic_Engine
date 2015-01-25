#include "../include/Rectangle.h"

GLuint antic::Rectangle::programID;
GLuint antic::Rectangle::vertexBufferID;
GLuint antic::Rectangle::colorBufferID;

GLfloat antic::Rectangle::colorDataR[]  = {
		1.f, 0.25f, 1.f,
		1.f, 0.25f, 1.f,
		1.f, 0.25f, 1.f,
		1.f, 0.25f, 1.f
	};

void antic::Rectangle::init()
{
	programID = agraph::ShaderFactory::loadShadersString("Default", agraph::vertexShaderString, agraph::fragmentShaderString)->getProgramID();
	// Generates and binds the vertex buffer, then loads it with the vertex buffer data.
	// This is basic OpenGL not wrapped by the Antic_Graph library.

	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	// Generates and binds the color buffer, then loads it with the color buffer data.
	// This is basic OpenGL not wrapped by the Antic_Graph library.
	
	glGenBuffers(1, &colorBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorDataR), colorDataR, GL_STATIC_DRAW);

	// Loads the identity for the orthographic projection.
	agraph::loadIdentity();
}

void antic::Rectangle::render(float x1, float y1, float r, float g, float b)
{
	//change color
	colorDataR[0] = r;
	colorDataR[3] = r;
	colorDataR[6] = r;
	colorDataR[9] = r;

	colorDataR[0+1] = g;
	colorDataR[3+1] = g;
	colorDataR[6+1] = g;
	colorDataR[9+1] = g;

	colorDataR[0+2] = b;
	colorDataR[3+2] = b;
	colorDataR[6+2] = b;
	colorDataR[9+2] = b;
	// Loads the shader.
	glUseProgram( programID );
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorDataR), colorDataR, GL_STATIC_DRAW);
	// Multiply matrices to get the MVC (Model, View, Projection matrix).
	glm::mat4 MVP = agraph::ProjectionOrtho * agraph::View * glm::translate(agraph::Model, glm::vec3(x1, y1, 0.0f));
	
	// Get the location of the MVP variable in the shader to later pass the MVP matrix data to it.
	GLuint MatrixID = glGetUniformLocation( programID, "MVP" );

	// Passes the MVP matrix to the shader.
	glUniformMatrix4fv( MatrixID, 1, GL_FALSE, &MVP[0][0] );

	// Get the vertexPosition and vertexColor variable locations from the shader to later be loaded with data.
	GLuint vertexPosition = glGetAttribLocation( programID, "vertexPosition" );
	GLuint vertexColor = glGetAttribLocation( programID, "vertexColor" );

	// Load the vertexPosition variable with the vertex buffer data.
	glEnableVertexAttribArray( vertexPosition );
	glBindBuffer( GL_ARRAY_BUFFER, vertexBufferID );
	glVertexAttribPointer( vertexPosition, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	// Load the vertexColor variable with the color buffer data.
	glEnableVertexAttribArray( vertexColor );
	glBindBuffer( GL_ARRAY_BUFFER, colorBufferID );
	glVertexAttribPointer( vertexColor, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	// This line renders the data passed to the shader.
	glDrawArrays( GL_TRIANGLE_FAN, 0, 3*4 );

	// Closes connections to the variables in the shader.
	glDisableVertexAttribArray( vertexPosition );
	glDisableVertexAttribArray( vertexColor );
}

void antic::Rectangle::cleanup()
{
	// Frees the vertex buffer object.
	if( vertexBufferID != 0 )
		glDeleteBuffers( 1, &vertexBufferID );

	// Frees the color buffer object.
	if( colorBufferID != 0 )
		glDeleteBuffers( 1, &colorBufferID );
}