#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D image;
uniform bool horizontal;

const int radius = 5;
float spreadBlur = 2.0f;
float weights[radius];

void main()
{
    float x = 0.0f;
    for (int i = 0; i < radius; i++)
    {
        if (spreadBlur <= 2.0f) {
            x += 3.0f / radius;
        }
        else {
            x += 6.0f / radius;
        }
        weights[i] = exp(-0.5f * pow(x / spreadBlur, 2.0f)) / (spreadBlur * sqrt(2 * 3.14159265f));
    }


    vec2 tex_offset = 1.0f / textureSize(image, 0);
    vec3 result = texture(image, TexCoords).rgb * weights[0];

    if(horizontal)
    {
        for(int i = 1; i < radius; i++)
        {
            result += texture(image, TexCoords + vec2(tex_offset.x * i, 0.0)).rgb * weights[i];
            result += texture(image, TexCoords - vec2(tex_offset.x * i, 0.0)).rgb * weights[i];
        }
    }
    else
    {
        for(int i = 1; i < radius; i++)
        {
            result += texture(image, TexCoords + vec2(0.0, tex_offset.y * i)).rgb * weights[i];
            result += texture(image, TexCoords - vec2(0.0, tex_offset.y * i)).rgb * weights[i];
        }
    }
    FragColor = vec4(result, 1.0f);
}