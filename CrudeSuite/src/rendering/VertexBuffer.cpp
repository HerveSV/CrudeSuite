//
//  VertexBuffer.cpp
//  CrudeEngine
//
//  Created by Hervé Schmit-Veiler on 4/26/20.
//  Copyright © 2020 Hervé Schmit-Veiler. All rights reserved.
//

#include "VertexBuffer.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


Crude::VertexBuffer::VertexBuffer(const void* data, unsigned int size) //size is bytecount of data
{
    glGenBuffers(1, &m_ID);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

Crude::VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_ID);
}

void Crude::VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void Crude::VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
