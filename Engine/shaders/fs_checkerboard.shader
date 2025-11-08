#version 330

out vec4 FragColour;
in vec3 FragPos;   // world-space from vertex shader
in vec2 TexCoords;

uniform float scale = 40.0;
uniform float checkSize = 0.1;
uniform vec3 colour1 = vec3(1.0, 1.0, 1.0); // white
uniform vec3 colour2 = vec3(0.0, 0.0, 0.0); // black

void main() {
    float pattern = mod(floor(FragPos.x * checkSize) + floor(FragPos.z * checkSize), 2.0);
    vec3 col = mix(colour1, colour2, pattern);
    FragColour = vec4(FragPos.x/20.0, FragPos.z/20.0, 0.0, 1.0);

}