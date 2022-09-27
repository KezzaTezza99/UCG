#ifndef __VERTEX_ARRAY__
#define __VERTEX_ARRAY__
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//TODO: Create a UTIL class to have typedefs for different byte sizes
class VertexArray
{
private:
	GLuint m_vertexArrayID;

public:
	VertexArray();
	~VertexArray();
	void Bind();	
};
#endif // !__VERTEX_ARRAY__

