#version 330

uniform mat4 uworldtrans;
uniform mat4 uviewproj;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

void main()
{

vec4 pos = vec4(inPosition,1.0);
pos *= uworldtrans;
pos *= uviewproj;

gl_Position = pos;
}