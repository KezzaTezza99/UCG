#include "TextureLoader.h"

TextureLoader::TextureLoader()
{
	glGenTextures(1, &m_textureID);
}

TextureLoader::~TextureLoader()
{
	glDeleteTextures(1, &m_textureID);
}

void TextureLoader::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void TextureLoader::SetTextureParams()
{
	//This should have a switch statment to swap on filter / wrapping options eventually
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
