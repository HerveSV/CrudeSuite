//
//  VertexBufferLayout.cpp
//  CrudeEngine
//
//  Created by Hervé Schmit-Veiler on 4/27/20.
//  Copyright © 2020 Hervé Schmit-Veiler. All rights reserved.
//

#include "VertexBufferLayout.hpp"

#include <GL/glew.h> 
#include <GLFW/glfw3.h>

unsigned int VertexBufferElement::getSizeOfType(unsigned int type)
{
    switch(type)
    {
        case GL_FLOAT:          return 4;
        case GL_UNSIGNED_INT:   return 4;
        case GL_UNSIGNED_BYTE:  return 1;
    }
    return 0;
}

template<> inline void VertexBufferLayout::push<float>(unsigned int count)
{
    m_elements.push_back(VertexBufferElement(GL_FLOAT, count, GL_FALSE));
    m_stride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
}

template<> inline void VertexBufferLayout::push<unsigned int>(unsigned int count)
{
    m_elements.push_back(VertexBufferElement(GL_UNSIGNED_INT, count, GL_FALSE));
    m_stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
}

template<> inline void VertexBufferLayout::push<unsigned char>(unsigned int count)
{
    m_elements.push_back(VertexBufferElement(GL_UNSIGNED_BYTE, count, GL_FALSE));
    m_stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
}
