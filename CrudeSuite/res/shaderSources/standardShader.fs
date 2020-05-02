#version 330 core
out vec4 FragColour;

in vec3 vColour;
in vec2 vTexCoord;

uniform sampler2D uTexture1;
uniform sampler2D uTexture2;
uniform sampler2D uTexture3;

uniform float uVisibility1 = 0.5f;
uniform float uVisibility2 = 0.5f;
uniform float uVisibility3 = 0.5f;

void main() {

    vec4 tex1 = texture(uTexture1, vTexCoord);
    vec4 tex2 = texture(uTexture2, vTexCoord);
    vec4 tex3 = texture(uTexture3, vTexCoord);
    
    FragColour = mix(mix(mix(vec4(vColour, 1.0f), tex1, uVisibility1), tex2, uVisibility2), tex3, uVisibility3);
    //mix(texture(uTexture1, vTexCoord), texture(uTexture2, vTexCoord), uVisibility2);
    //
    
    
}
