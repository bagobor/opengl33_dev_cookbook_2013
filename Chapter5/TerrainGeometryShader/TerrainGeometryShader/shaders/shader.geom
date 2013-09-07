#version 330 
layout (triangles) in;
layout (triangle_strip, max_vertices=3) out; 

uniform mat4 MVP;
uniform ivec2 HALF_TERRAIN_SIZE;
uniform sampler2D heightMapTexture;
uniform float scale;
uniform float half_scale;

void main()
{
	for(int i=0;i<gl_in.length(); i++) {
		vec4 vVertex = gl_in[i].gl_Position;
		float height = texture(heightMapTexture, vVertex.xz).r*scale - half_scale;
		vec2 xz = (vVertex.xz*2.0-1)*HALF_TERRAIN_SIZE;
		gl_Position = MVP*vec4(xz.x, height, xz.y, 1);	
		EmitVertex();		
	}
	EndPrimitive();
}