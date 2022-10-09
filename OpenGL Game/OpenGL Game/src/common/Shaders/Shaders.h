#ifndef __SHADERS__
#define __SHADERS__
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../../../Librairies/glm/mat4x4.hpp"
#include "../../../Librairies/glm/gtc/type_ptr.hpp"
#include "../Maths/vec3.h"

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

	//Setters
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetVec3(const std::string& name, maths::vec3 value) const;
	void SetMat4(const std::string& name, glm::mat4 value) const;
	//Getters
	GLuint GetID();
};
#endif // !__SHADERS__

