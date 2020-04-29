#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec2 aTexCoord; //Texture coordinates
//layout (location = 2) in vec3 aColour; // the color variable has attribute position 1


out vec3 vColour; // output a color to the fragment shader;
out vec2 vTexCoord;

uniform vec3 uColour;
uniform bool uReflectX = false; //reflecting shape in the x-axis
uniform bool uReflectY = false; //reflecting shape in the y-axis

uniform mat4 uMVP = mat4(1.0f);

void main() {
    
    vec3 tempPos = aPos;
    
    if(uReflectX)
    {
        tempPos.y = -aPos.y;
    }
    
    if(uReflectY)
    {
        tempPos.x = -aPos.x;
    }
    
    gl_Position = uMVP * vec4(tempPos, 1.0f);
    vTexCoord = aTexCoord;
    vColour = uColour;

    
}


