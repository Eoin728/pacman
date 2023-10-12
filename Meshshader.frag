#version 330



uniform vec3 ulightdir;
uniform vec3 udiffusecolour;
uniform vec3 uspeccolour;

uniform vec3 ucamerapos;

uniform vec3 uambient;

uniform float uspecpower;

//uniform lightstruct ulight;


in vec3 fragworldpos;
in vec3 fragnormal;
in vec2 fragtex;


out vec4 outcolour;
uniform sampler2D utex;

void main()
{
vec3 normal = normalize(fragnormal);

vec3 s2l = normalize(-ulightdir);

vec3 s2c = normalize(ucamerapos- fragworldpos);

vec3 reflec = normalize(reflect(-s2l,normal));

vec3 lting = uambient;

float x = dot(s2l,normal);

if (x > 0)
{
vec3 d = udiffusecolour * x;
vec3 s = uspeccolour * pow(max(0,dot(s2c,reflec)),uspecpower);
lting += d + s;
outcolour = texture(utex,fragtex) * vec4(lting,1.0f);
}
else{

outcolour = texture(utex,fragtex);

}
}