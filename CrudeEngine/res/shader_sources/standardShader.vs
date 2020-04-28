#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec2 aTexCoord; //Texture coordinates
//layout (location = 2) in vec3 aColour; // the color variable has attribute position 1


out vec3 ourColour; // output a color to the fragment shader;
out vec2 TexCoord;

uniform vec3 uColour;
//uniform float uaColourMix = 0.0f;
//uniform bool invert = false;
//uniform float xOffset = 0.0f;
//uniform float yOffset = 0.0f;

uniform mat4 model = mat4(1.0f);
uniform mat4 view = mat4(1.0f);
uniform mat4 projection = mat4(1.0f);

//uniform mat4 transform;

void main() {
    
    /*vec3 tempPos = aPos;
    if(invert)
    {
        tempPos.y = -tempPos.y;
    }
    tempPos.x += xOffset;
    tempPos.y += yOffset;
    gl_Position = projection * view * model * vec4(tempPos, 1.0f);
    ourColor = aColor; // set ourColor to the input color we got from the vertex data
    TexCoord = aTexCoord;*/
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    TexCoord = aTexCoord;
    ourColour = uColour;

    
}


