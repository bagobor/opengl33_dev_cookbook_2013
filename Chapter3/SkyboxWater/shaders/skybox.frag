#version 330

layout(location=0) out vec4 vFragColor;

uniform samplerCube cubeMap;

smooth in vec3 uv;
void main(void)
{
   vFragColor = texture(cubeMap, uv);
}