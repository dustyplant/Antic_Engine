#include <Antic/EngineVars.h>
#include <GL/glew.h>
#include <fstream>
#include <vector>

antic::EngineVars::~EngineVars()
{
	close();
}

GLuint antic::EngineVars::getShader( std::string name )
{
	auto iter = shaderMap.find( name );
	if( iter == shaderMap.end() )
	{
		printf("Error: EngineVars could not find shader name %s\n", name.c_str() );
		return 0;
	}

	return iter->second;
}

bool antic::EngineVars::loadProgram( std::string name, std::string vertexShaderPath, std::string fragmentShaderPath )
{
    auto iter = shaderMap.find( name );
    if( iter != shaderMap.end() )
    {
    	printf("Error: A shader is already loaded with name %s.\n", name.c_str());
    	return false;
    }

	GLuint vertexShaderID = glCreateShader( GL_VERTEX_SHADER );
    GLuint fragmentShaderID = glCreateShader( GL_FRAGMENT_SHADER );

  	if( loadShader( vertexShaderID, vertexShaderPath ) == false )
  		return false;

  	if( loadShader( fragmentShaderID, fragmentShaderPath ) == false )
  	{
  		glDeleteShader( vertexShaderID );
  		return false;
  	}

  	GLuint newProgramID = glCreateProgram();

  	glAttachShader( newProgramID, vertexShaderID );
  	glAttachShader( newProgramID, fragmentShaderID );

  	glLinkProgram( newProgramID );

  	glDeleteShader( vertexShaderID );
  	glDeleteShader( fragmentShaderID );

  	GLint success = 0;
  	glGetProgramiv( newProgramID, GL_LINK_STATUS, &success );
  	if( success == GL_FALSE )
  	{
  		printf("Error: Failed to link program %s.\n", name.c_str());
  		return false;
  	}

    shaderMap[ name ] = newProgramID;

	return true;
}

bool antic::EngineVars::loadProgramFromString( std::string name, std::string vertexShaderSource, std::string fragmentShaderSource )
{
	auto iter = shaderMap.find( name );
    if( iter != shaderMap.end() )
    {
    	printf("Error: A shader is already loaded with name %s.\n", name.c_str());
    	return false;
    }

	GLuint vertexShaderID = glCreateShader( GL_VERTEX_SHADER );
    GLuint fragmentShaderID = glCreateShader( GL_FRAGMENT_SHADER );

    char const * correctVertexShaderSource = vertexShaderSource.c_str();
  	glShaderSource( vertexShaderID, 1, &correctVertexShaderSource, nullptr );
    glCompileShader( vertexShaderID );

    GLint success = 0;
    glGetShaderiv( vertexShaderID, GL_COMPILE_STATUS, &success );
    if( success == GL_FALSE )
    {
    	printf("Error: Failed to compile vertex shader %s\n", name.c_str());

    	GLint maxLength = 0;
        glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &maxLength);
 
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShaderID, maxLength, &maxLength, &infoLog[0]);

        printf("%s\n", &infoLog[0]);

    	glDeleteShader( vertexShaderID );
    	return false;
    }

    char const * correctFragmentShaderSource = fragmentShaderSource.c_str();
    glShaderSource( fragmentShaderID, 1, &correctFragmentShaderSource, nullptr );
    glCompileShader( fragmentShaderID );

    glGetShaderiv( fragmentShaderID, GL_COMPILE_STATUS, &success );
    if( success == GL_FALSE )
    {
    	printf("Error: Failed to compile fragment shader %s\n", name.c_str());
    	glDeleteShader( fragmentShaderID );
    	return false;
    }

  	GLuint newProgramID = glCreateProgram();

  	glAttachShader( newProgramID, vertexShaderID );
  	glAttachShader( newProgramID, fragmentShaderID );

  	glLinkProgram( newProgramID );

  	glDeleteShader( vertexShaderID );
  	glDeleteShader( fragmentShaderID );

  	glGetProgramiv( newProgramID, GL_LINK_STATUS, &success );
  	if( success == GL_FALSE )
  	{
  		printf("Error: Failed to link program %s.\n", name.c_str());
  		return false;
  	}

    shaderMap[ name ] = newProgramID;

	return true;
}

bool antic::EngineVars::loadShader( GLuint shaderID, std::string shaderPath )
{
    std::string shaderSource = loadShaderSource( shaderPath );
    if( shaderSource == "" )
    {
    	printf("Error: Empty shader %s\n", shaderPath.c_str());
    	return false;
    }

    char const * correctShaderSource = shaderSource.c_str();
    glShaderSource( shaderID, 1, &correctShaderSource, nullptr );
    glCompileShader( shaderID );

    GLint success = 0;
    glGetShaderiv( shaderID, GL_COMPILE_STATUS, &success );
    if( success == GL_FALSE )
    {
    	printf("Error: Failed to compile shader %s\n", shaderPath.c_str());
    	glDeleteShader( shaderID );
    	return false;
    }

	return true;
}

void antic::EngineVars::close()
{
	for( auto iter: shaderMap )
	{
		if( iter.second != 0 )
			glDeleteProgram( iter.second );
	}
	shaderMap.clear();
}

std::string antic::EngineVars::loadShaderSource( std::string path )
{
	std::string shaderSource = "";
	std::ifstream ifs( path.c_str(), std::ios::in );
    if( ifs.is_open() )
    {
    	std::string currLine = "";
    	while( ifs.eof() == false )
    	{
    		getline( ifs, currLine );
    		shaderSource = shaderSource + '\n' + currLine;
    	}
    }
    else
    	printf("Error: Could not open shader at %s\n", path.c_str());

    ifs.close();

    return shaderSource;
}