#include "vertexarray.h"
#include "renderer.h"

//binds m_RendererID to vertex array
//when this function is called for the first time
vertexarray::vertexarray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

//Deletes the buffer from array
vertexarray::~vertexarray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

//add buffer to the vertex array
void vertexarray::addbuffer(const vertexbuffer& vb, const vertexbufferlayout& layout)
{
	Bind();
	vb.Bind();
	const auto elements = layout.GetElements();
	unsigned int offset = 0;
	for(unsigned int i = 0; i < elements.size(); i++ )
	{
		const auto element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i,element.count, element.type, element.normalized , layout.GetStride(),(const void*) offset));	
	
		offset += element.count * vertexbufferelement::GetSizeOfType(element.type);
	}
}

void vertexarray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void vertexarray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
