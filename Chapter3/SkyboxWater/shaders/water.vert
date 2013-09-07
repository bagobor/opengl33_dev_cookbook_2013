#version 330
  
layout(location=0) in vec3 vVertex; 

uniform mat4 MVP;  
//uniform mat3 N;				//normal matrix
uniform float time;

 
smooth out vec3 vNormal; 
smooth out vec3 vPosition;

  
const float PI = 3.14159;
const int NUM_WAVES = 4;
 
float frequencies[NUM_WAVES]=float[NUM_WAVES](16*PI,8*PI,PI/8.0,PI/16.0);
   
uniform vec2 directions[NUM_WAVES];
 
 


float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}



float wave(int i, vec2 xy) { 
	float speed = 1.0 + 2*i;
	float phase = speed*frequencies[i]; 
	vec2 direction = directions[i];
	float theta = dot(direction, xy);
	return  sin(theta*frequencies[i]+time*phase); 
}
 
float waveHeight(vec2 xy) {
	float height = 0;
	for(int i=0;i<NUM_WAVES;i++) {
		height += wave(i, xy)  ;
	}
	return height;
}
 

float waveDx(int i, vec2 xy) { 
	float speed = 1.0 + 2*i;
	float phase = speed*frequencies[i];
	float theta = dot(directions[i],xy);
	float A =  directions[i].x * frequencies[i];
	return A * cos(theta * frequencies[i] + time * phase);
}

float waveDy(int i, vec2 xy) { 
	float speed = 1.0 + 2*i;
	float phase = speed*frequencies[i];
	float theta = dot(directions[i], xy);
	float A =   directions[i].y * frequencies[i];
	return A * cos(theta * frequencies[i] + time * phase);
}

vec3 waveNormal(vec2 xy) {
	float dx = 0;
	float dy = 0;
	for(int i=0;i<NUM_WAVES;i++) {
		dx += waveDx(i, xy);
		dy += waveDy(i, xy);
	}
	return normalize(vec3(-dx, 1.0, -dy));
}

void main()
{ 	 	  
	vec4 pos = vec4(vVertex,1);
	float offset = rand(vVertex.xz);
    pos.y = (waveHeight(vVertex.xz +  offset )) * 0.1;
    vPosition = pos.xyz / pos.w;
    vNormal = waveNormal(vVertex.xz + offset);    
	gl_Position = MVP*pos; 
}