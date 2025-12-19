#include "VertexBuffer.h"
#include "Renderer.h"
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &m_RendererID); // size, generate id for later
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); // bind to buffer type
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); // copy user data to gpu mem
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID))
}

void VertexBuffer::Bind() const 
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const 
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}