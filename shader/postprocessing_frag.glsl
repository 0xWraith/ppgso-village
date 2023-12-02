#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D scene;
uniform sampler2D bloomBlur;
uniform float exposure;

uniform float time;
uniform float noiseSize = 1;
uniform float noiseAmount = 0.3;

uniform bool bloom;
uniform bool noise;

uint hash( uint x ) {
    x += ( x << 10u );
    x ^= ( x >>  6u );
    x += ( x <<  3u );
    x ^= ( x >> 11u );
    x += ( x << 15u );
    return x;
}



uint hash( uvec2 v ) { return hash( v.x ^ hash(v.y)                         ); }
uint hash( uvec3 v ) { return hash( v.x ^ hash(v.y) ^ hash(v.z)             ); }
uint hash( uvec4 v ) { return hash( v.x ^ hash(v.y) ^ hash(v.z) ^ hash(v.w) ); }



float floatConstruct( uint m ) {
    const uint ieeeMantissa = 0x007FFFFFu;
    const uint ieeeOne      = 0x3F800000u;

    m &= ieeeMantissa;
    m |= ieeeOne;

    float  f = uintBitsToFloat( m );
    return f - 1.0;
}

float random( float x ) { return floatConstruct(hash(floatBitsToUint(x))); }
float random( vec2  v ) { return floatConstruct(hash(floatBitsToUint(v))); }
float random( vec3  v ) { return floatConstruct(hash(floatBitsToUint(v))); }
float random( vec4  v ) { return floatConstruct(hash(floatBitsToUint(v))); }

void main()
{
    const float gamma = 1.0;
    vec3 hdrColor = texture(scene, TexCoords).rgb;
    vec3 bloomColor = texture(bloomBlur, TexCoords).rgb;
    if(bloom) {
        hdrColor += bloomColor;
    }
    vec4 bloomView = vec4(pow(vec3(1.0) - exp(-hdrColor * exposure), vec3(1.0 / gamma)), 1.0);
    vec3 inputs = vec3(gl_FragCoord.xy, time);
    float rand = (random( inputs * noiseSize ) - 0.5) * noiseAmount;
    vec4 finalView;
    if(noise) {
        finalView = (bloomView + vec4(rand, rand, rand, 0.0 )) * 0.7;
    } else {
        finalView = bloomView;
    }
    FragColor = finalView;
}
