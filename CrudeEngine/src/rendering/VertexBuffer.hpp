//
//  VertexBuffer.hpp
//  CrudeEngine
//
//  Created by Hervé Schmit-Veiler on 4/26/20.
//  Copyright © 2020 Hervé Schmit-Veiler. All rights reserved.
//

#ifndef VertexBuffer_hpp
#define VertexBuffer_hpp

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexBuffer
{
private:
    unsigned int m_ID;
public:
    VertexBuffer(const void* data, unsigned int size); //size is bytecount of data
    ~VertexBuffer();
    
    void bind() const;
    void unbind() const;
    
    inline unsigned int getID() const {return m_ID;}
};


#endif /* VertexBuffer_hpp */
