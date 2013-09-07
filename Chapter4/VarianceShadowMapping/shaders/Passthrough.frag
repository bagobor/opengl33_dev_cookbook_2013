#version 330 core
  
layout(location=0) out vec4 vColor;  
smooth in vec2 vUV;

uniform sampler2D textureMap;

void main()
{ 	 
	vColor = texture(textureMap, vUV);
}