#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float time;
uniform float noiseSize = 1;
uniform float noiseAmount = 0.3;

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
    vec4 originalColor = texture(screenTexture, TexCoords);
    vec3  inputs = vec3( gl_FragCoord.xy, time );
    float rand   = (random( inputs * noiseSize ) - 0.5) * noiseAmount;
    vec4 noisyColor = (originalColor + vec4( rand, rand, rand, 0.0 )) * 0.8;
    FragColor = noisyColor;
}