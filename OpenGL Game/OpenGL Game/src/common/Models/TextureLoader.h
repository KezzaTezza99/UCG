#ifndef __TEXTURE_LOADER__
#define __TEXTURE_LOADER__
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class TextureLoader
{
private:
	GLuint m_textureID;

public:
	TextureLoader();
	~TextureLoader();
	void Bind();
	//TODO: This should take in a number eventually to decide what type to filter / wrap by? 
	void SetTextureParams();
};
#endif //!__TEXTURE_LOADER__

