#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_vertexArrayID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
}

void VertexArray::Bind()
{
	glBindVertexArray(m_vertexArrayID);
}