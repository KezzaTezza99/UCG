#ifndef __VERTEX__
#define __VERTEX__
#include <vector>
#include <GLFW/glfw3.h>
#include "../../../Librairies/glm/vec3.hpp"
#include "../../../Librairies/glm/vec2.hpp"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normals;
	glm::vec3 colour;
	glm::vec2 uvs;
};
#endif //!__VERTEX__
