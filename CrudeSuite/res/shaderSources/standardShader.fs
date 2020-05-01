#version 330 core
out vec4 FragColour;

in vec3 vColour;
in vec2 vTexCoord;

uniform sampler2D uTexture1;
uniform sampler2D uTexture2;
uniform sampler2D uTexture3;

uniform float uVisibility1 = 1.0f;
uniform float uVisibility2 = 0.0f;
uniform float uVisibility3 = 0.0f;

void main() {

    vec4 tex1 = texture(uTexture1, vTexCoord);
    vec4 tex2 = texture(uTexture2, vTexCoord);
    vec4 tex3 = texture(uTexture3, vTexCoord);
    
    FragColour = tex2;
    //mix(mix(mix(vec4(vColour, 1.0f), texture(uTexture1, vTexCoord), uVisibility1), texture(uTexture2, vTexCoord), uVisibility2), texture(uTexture3, vTexCoord), uVisibility3);
    
    
}
