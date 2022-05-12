#pragma once
class indexbuffer
{
    private:
    	//variables only used by files connected to this header file
        unsigned int m_RendererID;
        unsigned int m_Count;
    public:
    	//defining "__init__":
        indexbuffer(const unsigned int * data, unsigned int size);

	//exit function, runs when the program exits
        ~indexbuffer();
	
	//creating bind and unbind buffers
        void Bind() const;
        void Unbind() const;
	

	//returns the value of m_Count when called 
        inline unsigned int GetCount() const
	{
		return m_Count;
	}
};
