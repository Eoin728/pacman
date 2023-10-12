#version 330

//this is probanly bad and stuff
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexcoord;

uniform mat4 uworldtrans;
uniform mat4 uviewproj;

out vec3 fragworldpos;
out vec3 fragnormal;
out vec2 fragtex;


void main()
{
	vec4 pos = vec4(inPosition,1.0);
	pos *= uworldtrans;
	fragworldpos = pos.xyz;

	pos *= uviewproj;

	gl_Position = pos;

	fragnormal = ( vec4(inNormal,0.0) * uworldtrans).xyz;
	fragtex = inTexcoord;
}