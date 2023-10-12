#version 330



in vec3 fragworldpos;
in vec3 fragnormal;
in vec2 fragtex;



out vec4 outcolour;
uniform sampler2D utex;

void main()
{


outcolour = texture(utex,fragtex) ;
//outcolour = vec4(1,0,0,1);
}