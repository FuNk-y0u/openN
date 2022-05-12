#include "indexbuffer.h"
#include "renderer.h"
#include<GL/glew.h>

// adding code inside "__init__" function
indexbuffer::indexbuffer(const unsigned int* data, unsigned int count)
    :m_Count(count)
{
	//checking if "unsigned int"'s size is equal to GLuint
	//If false ASSERT() closes the program
    	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	//generates buffer as m_RendererID
    	GLCall(glGenBuffers(1, &m_RendererID));

	//Selects the buffer
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));

	//Adds Data to buffer
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER,count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

indexbuffer::~indexbuffer()
{
	//Deletes buffer when program closes
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void indexbuffer::Bind()const 
{
	//binds the buffer 
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_RendererID));
}

void indexbuffer::Unbind()const
{
	//Clears the buffer from bind
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0));
}
