#version 330 core
out vec4 FragColour;
in vec3 colour;

void main()
{
   FragColour = vec4(colour, 1.0f);
}