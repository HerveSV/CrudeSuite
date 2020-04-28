//
//  VertexArray.hpp
//  CrudeEngine
//
//  Created by Hervé Schmit-Veiler on 4/27/20.
//  Copyright © 2020 Hervé Schmit-Veiler. All rights reserved.
//

#ifndef VertexArray_hpp
#define VertexArray_hpp

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray
{
private:
    unsigned int m_ID;
public:
    VertexArray();
    ~VertexArray();
    
    void bind() const;
    void unbind() const;
    
    void addVertexBuffer(VertexBuffer &vbo, VertexBufferLayout &layout);
    void addIndexBuffer(IndexBuffer &ebo);
    
    inline unsigned int getID() const {return m_ID;}
    
};
#endif /* VertexArray_hpp */
