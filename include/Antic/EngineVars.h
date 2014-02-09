/*
#ifndef ENGINEVARS_H
#define ENGINEVARS_H

#include <iostream>
#include <map>
#include <GL/glew.h>

namespace antic
{
	class EngineVars
	{
	public:
		virtual ~EngineVars();

		GLuint getShader( std::string name );
		bool loadProgram( std::string name, std::string vertexShaderPath, std::string fragmentShaderPath );
		bool loadProgramFromString( std::string name, std::string vertexShaderSource, std::string fragmentShaderSource );

	private:
		bool loadShader( GLuint shaderID, std::string shaderPath );
		//bool loadShader( GLuint shaderID, std::string shaderPath );
		std::string loadShaderSource( std::string path );

		void close();
		std::map< std::string, GLuint > shaderMap;
	};
}

#endif
*/