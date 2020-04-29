//
//  IndexBuffer.hpp
//  CrudeEngine
//
//  Created by Hervé Schmit-Veiler on 4/26/20.
//  Copyright © 2020 Hervé Schmit-Veiler. All rights reserved.
//

#ifndef IndexBuffer_hpp
#define IndexBuffer_hpp

#include <stdio.h>


class IndexBuffer
{
private:
    unsigned int m_ID;
    unsigned int m_count;
public:
    IndexBuffer(const unsigned int* data, unsigned int count); //count is element count of data
    ~IndexBuffer();
    
    void bind() const;
    void unbind() const;
    
    inline unsigned int getCount() {return m_count;}
    inline unsigned int getID() const {return m_ID;}
    
};


#endif /* IndexBuffer_hpp */
