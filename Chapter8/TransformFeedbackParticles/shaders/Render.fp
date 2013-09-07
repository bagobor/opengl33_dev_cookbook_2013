#version 330 core

layout(location=0) smooth out vec4 vFragColor;
smooth in vec4 color; 

void main()
{ 		
	vFragColor = color;  	
}