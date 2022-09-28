#ifndef __SHADERS__
#define __SHADERS__
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

//TODO: When I implement uniforms need some helper methods to set them
class Shaders
{
private:
	GLuint m_shaderID;
	const char* m_vertexShader;
	const char* m_fragmentShader;

public:
	void LoadShader(const char* vertexShaderPath, const char* fragmentShaderPath);
	void ActivateShaders();

	//Getters
	GLuint GetID();
};
#endif // !__SHADERS__

