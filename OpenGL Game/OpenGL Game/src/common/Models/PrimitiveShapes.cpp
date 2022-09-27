#include "PrimitiveShapes.h"
#include <iostream>

GLfloat* PrimitiveShapes::DrawTriangle(maths::vec3 bottomLeft, maths::vec3 bottomRight, maths::vec3 top)
{
	GLfloat vertices[] =
	{
		bottomLeft.x, bottomLeft.y, bottomLeft.z,
		bottomRight.x, bottomRight.y, bottomRight.z,
		top.x, top.y, top.z
	};

#if 1
	//Debug
	std::cout << "Debug Info (Primitive Shapes) -" << "		" << "Vertices " << vertices << std::endl;
	return vertices;
#endif
}
