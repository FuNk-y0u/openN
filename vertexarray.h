#pragma once
#include "vertexbuffer.h"
#include "vertexbufferlayout.h"

class vertexarray
{
	private:
		unsigned int m_RendererID;
	public:
		vertexarray();
		~vertexarray();

		void addbuffer(const vertexbuffer& vb, const vertexbufferlayout& layout);

		void Bind() const;
		void Unbind() const;
};
