#version 330

layout(location=0) out vec4 vFragColor; 
uniform samplerCube cubeMap;   

smooth in vec3 vNormal; 
smooth in vec3 vPosition;

uniform vec3 eyePos;
 
void main(void)
{ 
	vec3 eye = normalize(vPosition-eyePos);
    vec3 r = reflect(eye, vNormal);
    vec4 color = texture(cubeMap, r);
    color.a = 0.5;
    vFragColor =  vec4(vNormal,1);//color;
}