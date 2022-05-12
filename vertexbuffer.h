#pragma once
class vertexbuffer
{
    private:
        unsigned int m_RendererID;
    public:
        vertexbuffer(const void * data, unsigned int size);
        ~vertexbuffer();

        void Bind()const;
        void Unbind()const;
};
