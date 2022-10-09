#ifndef __MESH__
#define __MESH__
#include <vector>
#include "Vertex.h"
#include "Texture.h"

class Mesh
{
private:
	unsigned int VAO, VBO, IBO;
	void SetupMesh();

public:
	//Mesh Data
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void DrawMesh(Shader& shader);
};
#endif
//https://learnopengl.com/Model-Loading/Mesh