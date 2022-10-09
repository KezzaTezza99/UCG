#include "Shaders.h"

void Shaders::LoadShader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	//Getting the source code from the defined file paths
	std::string vertexSourceCode;
	std::string fragmentSourceCode;
	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;

	//Allowing ifstream to throw expceptions if needed
	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//Opening the files
		vertexShaderFile.open(vertexShaderPath);
		fragmentShaderFile.open(fragmentShaderPath);

		//Reading the files to a buffer
		std::stringstream vertexStream, fragmentStream;
		vertexStream << vertexShaderFile.rdbuf();
		fragmentStream << fragmentShaderFile.rdbuf();

		//Closing the file hadnlers
		vertexShaderFile.close();
		fragmentShaderFile.close();

		//Converting the stream into a string
		vertexSourceCode = vertexStream.str();
		fragmentSourceCode = fragmentStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR: Shader file not successfully read" << std::endl;
	}

	//Setting the member variables to keep a copy of the src code that is persistent
	m_vertexShader = vertexSourceCode.c_str();
	m_fragmentShader = fragmentSourceCode.c_str();

	//Compiling the shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	//Vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &m_vertexShader, NULL);
	glCompileShader(vertex);

	//Display compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR: Vertex shader not successfully compiled\n" << infoLog << std::endl;
	};

	//Fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &m_fragmentShader, NULL);
	glCompileShader(fragment);

	//Display compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR: Fragment shader not successfully compiled\n" << infoLog << std::endl;
	};

	//Creating the shader program
	m_shaderID = glCreateProgram();
	glAttachShader(m_shaderID, vertex);
	glAttachShader(m_shaderID, fragment);
	glLinkProgram(m_shaderID);

	//Display any linking errors
	glGetProgramiv(m_shaderID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_shaderID, 512, NULL, infoLog);
		std::cout << "ERROR: Shader linking failed\n" << infoLog << std::endl;
	}

	//Deleting the shaders as they are now linked
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shaders::ActivateShaders()
{
	glUseProgram(m_shaderID);
}

void Shaders::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_shaderID, name.c_str()), (int)value);
}

void Shaders::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_shaderID, name.c_str()), value);
}

void Shaders::SetFloat(const std::string& name, float value) const
{
	glUniform1i(glGetUniformLocation(m_shaderID, name.c_str()), value);
}

void Shaders::SetVec3(const std::string& name, maths::vec3 value) const
{
	glUniform3i(glGetUniformLocation(m_shaderID, name.c_str()), value.x, value.y, value.z);
}

void Shaders::SetMat4(const std::string& name, glm::mat4 value) const
{
	glUniformMatrix4fv(m_shaderID, 1, GL_FALSE, glm::value_ptr(value));
}

GLuint Shaders::GetID()
{
	return m_shaderID;
}
