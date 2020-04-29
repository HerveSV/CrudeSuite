//
//  VertexBufferLayout.hpp
//  CrudeEngine
//
//  Created by Hervé Schmit-Veiler on 4/27/20.
//  Copyright © 2020 Hervé Schmit-Veiler. All rights reserved.
//

#ifndef VertexBufferLayout_hpp
#define VertexBufferLayout_hpp

#include <stdio.h>
#include <vector>

class VertexBufferElement
{
public:
    unsigned int type;
    unsigned int count;
    unsigned int normalised;
    
    VertexBufferElement(unsigned int c_type, unsigned int c_count, unsigned int c_normalised)
    : type(c_type), count(c_count), normalised(c_normalised)
    {
        
    }
    
    static unsigned int getSizeOfType(unsigned int type);
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_elements;
    unsigned int m_stride;
public:
    
    VertexBufferLayout() : m_stride(0) {};
    //~VertexBufferLayout();
    
    template <typename T>
    void push(unsigned int count)
    {
        //static_assert(false, "Unspecified!");
    }
    
    /*template<>
    void Push<float>(unsigned int count)
    {
        m_elements.push_back(VertexBufferElement(GL_FLOAT, count, GL_FALSE));
        m_stride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
    }
    
    template<>
    void Push<unsigned int>(unsigned int count)
    {
        m_elements.push_back(VertexBufferElement(GL_UNSIGNED_INT, count, GL_FALSE));
        m_stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
    }
    
    template<>
    void Push<unsigned char>(unsigned int count)
    {
        m_elements.push_back(VertexBufferElement(GL_UNSIGNED_BYTE, count, GL_TRUE));
        m_stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
    }
    /**/
    inline const std::vector<VertexBufferElement> getElements() const {return m_elements;}
    inline unsigned int getStride() const {return m_stride;}
};


#endif /* VertexBufferLayout_hpp */
