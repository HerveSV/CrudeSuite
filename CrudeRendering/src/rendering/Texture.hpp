//
//  Texture.hpp
//  CrudeEngine
//
//  Created by Hervé Schmit-Veiler on 4/26/20.
//  Copyright © 2020 Hervé Schmit-Veiler. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include <iostream>

#include <string>
#include "stb_image.h"


class Texture
{
private:
    unsigned int m_ID;
    std::string m_filepath;
    unsigned char* m_localBuffer;
    int m_width, m_height, m_BPP; //Bits Per Pixel
    unsigned int m_slot;
public:
    Texture(std::string filepath, unsigned int colourFormat, bool verticalFlip = true);
    ~Texture();
    
    void bind(unsigned int slot = 0);
    void unbind();
    
    inline int getWidth() const {return m_width;}
    inline int getHeight() const {return m_height;}
    inline unsigned int getID() const {return m_ID;}
    
    
    
};

#endif /* Texture_hpp */
