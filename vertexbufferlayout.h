#pragma once
#include<vector>
#include<GL/glew.h>
#include"renderer.h"

struct vertexbufferelement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
    	switch(type)
	{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		
	}
	ASSERT(false);
	return 0;
    }
};


class vertexbufferlayout
{
    private:
        std::vector<vertexbufferelement> m_elements;
        unsigned int m_Stride;
    public:
        vertexbufferlayout()
            :m_Stride(0){}

        void push_float(int count)
        {
            m_elements.push_back({GL_FLOAT, count, GL_FALSE});
            m_Stride += vertexbufferelement::GetSizeOfType(GL_FLOAT) * count;
        }


        void push_unsignedint(int count)
        {
            m_elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
            m_Stride += vertexbufferelement::GetSizeOfType(GL_UNSIGNED_INT);
        }

        void push_unsignedchar(int count)
        {
            m_elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
            m_Stride += vertexbufferelement::GetSizeOfType(GL_UNSIGNED_BYTE);
        }

        inline const std::vector<vertexbufferelement> GetElements() const { return m_elements;}
        inline unsigned int GetStride() const {return m_Stride;}

};
