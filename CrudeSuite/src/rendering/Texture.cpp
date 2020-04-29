//
//  Texture.cpp
//  CrudeEngine
//
//  Created by Hervé Schmit-Veiler on 4/26/20.
//  Copyright © 2020 Hervé Schmit-Veiler. All rights reserved.
//

#include "Texture.hpp"

#include <GL/glew.h> 
#include <GLFW/glfw3.h>

Crude::Texture::Texture(std::string filepath, unsigned int colourFormat, bool verticalFlip) //colourFormat is the external format
: m_ID(0), m_filepath(filepath), m_localBuffer(nullptr), m_width(0), m_height(0), m_BPP(0), m_slot(0)
{
    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    stbi_set_flip_vertically_on_load(verticalFlip);
    m_localBuffer = stbi_load(m_filepath.c_str(), &m_width, &m_height, &m_BPP, colourFormat == GL_RGBA ? 4 : 0);
    if(m_localBuffer)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, colourFormat, GL_UNSIGNED_BYTE, m_localBuffer);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(m_localBuffer);
    }
    else
    {
       
        std::cout << "Failed to load texture: " << m_filepath << std::endl;
    }
    
    glBindTexture(GL_TEXTURE_2D, 0);
   
}

Crude::Texture::~Texture()
{
    glDeleteTextures(1, &m_ID);
}

void Crude::Texture::bind(unsigned int slot)
{
    assert(slot <= GL_MAX_TEXTURE_UNITS && "slot exceed maximum texture units available!");
    m_slot = slot;
    glActiveTexture(GL_TEXTURE0 + m_slot);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Crude::Texture::unbind()
{
    glActiveTexture(GL_TEXTURE0 + m_slot);
    glBindTexture(GL_TEXTURE_2D, 0);
}
