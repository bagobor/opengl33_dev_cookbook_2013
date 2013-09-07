#version 330
  
layout(location=0) in vec3 vVertex; 

uniform mat4 MVP; 

smooth out vec3 uv;
void main()
{ 	 	
	gl_Position = MVP*vec4(vVertex,1);
	uv = vVertex;
}