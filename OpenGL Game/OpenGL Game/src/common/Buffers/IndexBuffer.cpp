#include "IndexBuffer.h"

IndexBuffer::IndexBuffer()
{
	glGenBuffers(1, &m_indexBufferID);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_indexBufferID);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
}
