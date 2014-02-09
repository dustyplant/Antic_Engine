#include <Antic/Texture.h>
#include <IL/ilu.h>

antic::Texture::Texture( antic::Services *services ) : width( 0.0f ), height( 0.0f ), path( "" ), textureID( 0 ), position( glm::vec2(0,0) )
{
	this->services = services;
	GLuint programID = services->getEngineVars()->getShader("Default");
	textureSamplerID = glGetUniformLocation( programID, "tex" );
}

antic::Texture::~Texture()
{
	close();
}

bool antic::Texture::loadImage( std::string path )
{
	close();

	ILuint imgID;
	ilGenImages( 1, &imgID );
	ilBindImage( imgID );

	if( ilLoadImage( path.c_str() ) == false )
	{
		ILenum error = ilGetError();
		if( error != IL_NO_ERROR )
		{
			ilDeleteImages( 1, &imgID );
			printf("Error: Didn't load file %s.\n", path.c_str() );
			return false;
		}
	}

	width = ilGetInteger( IL_IMAGE_WIDTH );
	height = ilGetInteger( IL_IMAGE_HEIGHT );

	glGenTextures( 1, &textureID );
	glBindTexture( GL_TEXTURE_2D, textureID );

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData() );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

	glBindTexture( GL_TEXTURE_2D, 0 );
	ilDeleteImages( 1, &imgID );


	genBuffers();


	return true;
}

void antic::Texture::genBuffers()
{
	/*
	const GLfloat vertexBufferData[] = {
		0.0f, 				0.0f,				0.0f,
		(GLfloat)width, 	0.0f,				0.0f,
		(GLfloat)width, 	(GLfloat)height,	0.0f,
		0.0f, 				(GLfloat)height,	0.0f
	};
	*/
	GLfloat w = 1.0f / width / 2.0f;
	GLfloat h = 1.0f / height / 2.0f;
	const GLfloat vertexBufferData[] = 
	{
		-1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f
	};

	static const GLfloat uvBufferData[] = 
	{
		-1.0f,  1.0f,
		 1.0f,  1.0f,
		 1.0f, -1.0f,
		-1.0f, -1.0f
	};

	if( vertexArrayID != 0 )
		glDeleteVertexArrays( 1, &vertexArrayID );
	if( vertexBufferID != 0 )
		glDeleteBuffers( 1, &vertexBufferID );
	if( uvBufferID != 0 )
		glDeleteBuffers( 1, &uvBufferID );

	glGenVertexArrays( 1, &vertexArrayID );
	glBindVertexArray( vertexArrayID );

	glGenBuffers( 1, &vertexBufferID );
	glBindBuffer( GL_ARRAY_BUFFER, vertexBufferID );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertexBufferData ), vertexBufferData, GL_STATIC_DRAW );

	glGenBuffers( 1, &uvBufferID );
	glBindBuffer( GL_ARRAY_BUFFER, uvBufferID );
	glBufferData( GL_ARRAY_BUFFER, sizeof( uvBufferData ), uvBufferData, GL_STATIC_DRAW );
}

void antic::Texture::render()
{
	glBindVertexArray( vertexArrayID );

	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, textureID );
	glUniform1i( textureSamplerID, 0 );

	glEnableVertexAttribArray( 0 );
	glBindBuffer( GL_ARRAY_BUFFER, vertexBufferID );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	glEnableVertexAttribArray( 1 );
	glBindBuffer( GL_ARRAY_BUFFER, uvBufferID );
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	glDrawArrays( GL_QUADS, 0, 4 );

	glDisableVertexAttribArray( 0 );
	glDisableVertexAttribArray( 1 );
}

GLuint antic::Texture::getWidth()
{
	return width;
}

GLuint antic::Texture::getHeight()
{
	return height;
}

std::string antic::Texture::getPath()
{
	return path;
}

void antic::Texture::close()
{
	if( textureID  != 0 )
		glDeleteTextures( 1, &textureID );
	if( vertexArrayID != 0 )
		glDeleteVertexArrays( 1, &vertexArrayID );
	if( vertexBufferID != 0 )
		glDeleteBuffers( 1, &vertexBufferID );
	if( uvBufferID != 0 )
		glDeleteBuffers( 1, &uvBufferID );
}