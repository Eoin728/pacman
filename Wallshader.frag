#version 330

uniform vec3 ucolour;

out vec4 colour;

void main()
{

colour = vec4(ucolour,1.0);



}