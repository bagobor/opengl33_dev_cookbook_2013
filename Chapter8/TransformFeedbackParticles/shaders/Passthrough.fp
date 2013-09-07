#version 330 core

layout(location=0) smooth out vec4 vFragColor;
uniform vec4 vColor;

void main()
{ 		
	vFragColor = vColor;  	
}