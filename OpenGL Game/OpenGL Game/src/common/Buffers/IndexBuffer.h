#ifndef __INDEX_BUFFER__
#define __INDEX_BUFFER__
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class IndexBuffer
{
private:
	GLuint m_indexBufferID;

public:
	IndexBuffer();
	~IndexBuffer();
	void Bind();
};
#endif // !__INDEX_BUFFER__

