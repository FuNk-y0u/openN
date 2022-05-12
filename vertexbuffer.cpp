#include "vertexbuffer.h"
#include "renderer.h"

vertexbuffer::vertexbuffer(const void* data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER,size, data, GL_STATIC_DRAW));
}

vertexbuffer::~vertexbuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void vertexbuffer::Bind()const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER,m_RendererID));
}

void vertexbuffer::Unbind()const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER,0));
}
