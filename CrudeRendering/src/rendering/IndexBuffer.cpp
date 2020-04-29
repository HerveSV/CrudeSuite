//
//  IndexBuffer.cpp
//  CrudeEngine
//
//  Created by Hervé Schmit-Veiler on 4/26/20.
//  Copyright © 2020 Hervé Schmit-Veiler. All rights reserved.
//

#include "IndexBuffer.hpp"
#include <GL/glew.h> 
#include <GLFW/glfw3.h>

Crude::IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) //count is element count of data
{
    glGenBuffers(1, &m_ID);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    
}

Crude::IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_ID);
}

void Crude::IndexBuffer::bind() const
{
    glBindBuffer(1, m_ID);
}

void Crude::IndexBuffer::unbind() const
{
    glBindBuffer(1, 0);
}
