#ifndef __PRIMITIVE_SHAPES__
#define __PRIMITIVE_SHAPES__
#include <GLFW/glfw3.h>
#include "../Maths/vec3.h"

//TODO: Add more shapes
class PrimitiveShapes
{
public:
	GLfloat* DrawTriangle(maths::vec3 bottomLeft, maths::vec3 bottomRight, maths::vec3 top);
};
#endif // !__PRIMITIVE_SHAPES__

