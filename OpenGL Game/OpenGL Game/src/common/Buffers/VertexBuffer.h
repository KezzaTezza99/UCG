#ifndef __VERTEX_BUFFER__
#define __VERTEX_BUFFER__
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VertexBuffer
{
private:
	GLuint m_vertexBufferID;

public:
	VertexBuffer();
	~VertexBuffer();
	void Bind();
};
#endif // !__VERTEX_BUFFER__

