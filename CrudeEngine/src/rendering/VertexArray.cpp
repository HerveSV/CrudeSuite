//
//  VertexArray.cpp
//  CrudeEngine
//
//  Created by Hervé Schmit-Veiler on 4/27/20.
//  Copyright © 2020 Hervé Schmit-Veiler. All rights reserved.
//

#include "VertexArray.hpp"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_ID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_ID);
}

void VertexArray::bind() const
{
    glBindVertexArray(m_ID);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::addVertexBuffer(VertexBuffer &vbo, VertexBufferLayout &layout)
{
    bind();
    vbo.bind();
    const auto &elements = layout.getElements();
    unsigned int offset = 0;
    for(unsigned int i = 0; i < elements.size(); ++i)
    {
        const auto &element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalised, layout.getStride(), (void*)offset);
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
    
}

void VertexArray::addIndexBuffer(IndexBuffer &ebo)
{
    bind();
    ebo.bind();
}
