#version 330 core
out vec4 FragColour;

in vec3 ourColour;
in vec2 TexCoord;

uniform sampler2D uTexture1;
uniform sampler2D uTexture2;
uniform sampler2D uTexture3;

uniform float uVisibility1 = 1.0f;
uniform float uVisibility2 = 0.0f;
uniform float uVisibility3 = 0.0f;

void main() {

    //FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0f-TexCoord.x, TexCoord.y)), tex2Visibility);
    FragColour = mix(mix(mix(vec4(ourColour, 1.0f), texture(uTexture1, TexCoord), uVisibility1), texture(uTexture2, TexCoord), uVisibility2), texture(uTexture3, TexCoord), uVisibility3);
    //vec4(ourColour, 1.0f);
}
