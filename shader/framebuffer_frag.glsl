#version 330 core

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform sampler2D noiseTexture;
uniform sampler2D bloomTexture;
uniform float gamma;

void main()
{
    vec3 col = texture(screenTexture, TexCoords).rgb;
//    vec3 bloom = texture(bloomTexture, TexCoords).rgb;
//    vec3 noise = texture(noiseTexture, TexCoords).rgb;
//    vec3 color = col + noise * 0.1 + bloom * 5.5;
    FragColor = texture(noiseTexture, TexCoords);
}


