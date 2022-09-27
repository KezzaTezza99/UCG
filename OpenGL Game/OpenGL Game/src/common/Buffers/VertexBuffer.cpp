#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &m_vertexBufferID);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_vertexBufferID);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
}