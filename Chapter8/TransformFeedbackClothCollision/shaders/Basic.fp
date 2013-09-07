#version 330

smooth out vec4 vFragColor;
smooth in vec4 oColor;

void main()
{ 		
	//The equation is sqrt(dot(gl_PointCoord-0.5,gl_PointCoord-0.5)>0.5)	
	//square bth sides gives this
	/*vec2 p = gl_PointCoord* 2.0 -1;
	if(dot(p,p) > 1.0)
		discard;
	else 
		vFragColor = vColor;
	*/
	
	if(dot(gl_PointCoord-0.5,gl_PointCoord-0.5)>0.25)	
		discard;
	else
		vFragColor = oColor;  
	

	//flower shaped
	/*
	vec2 p = gl_PointCoord* 2.0 - vec2(1.0);
	float r = sqrt(dot(p,p));
	float theta = atan(p.y,p.x);
	if(dot(p,p) > cos(theta*5))
		discard;
	else 
		vFragColor = vColor;
*/
	//or this 
/*
	vec2 p = gl_PointCoord* 2.0 - vec2(1.0);
	if(dot(p,p) > sin(atan(p.y,p.x)*5))
		discard;
	else 
		vFragColor = oColor;
*/	

	//ring shape
	/*
	vec2 p = gl_PointCoord* 2.0 - vec2(1.0);
	float r = sqrt(dot(p,p));
	float theta = atan(p.y,p.x);
	if(dot(p,p) > r || dot(p,p)<r*0.75)
		discard;
	else 
		vFragColor = oColor;
	*/

	//spiral
	/*vec2 p = gl_PointCoord* 2.0 - vec2(1.0);
	float r = sqrt(dot(p,p));
	float theta = atan(p.y,p.x);
	
	if(dot(p,p)> 5.0/cos(theta-20*r))
		discard;
	else 
		vFragColor = vColor;
	
*/
	//two triangles
	/*
	vec2 p = gl_PointCoord* 2.0 - vec2(1.0);
	if(dot(p,p) > 50*cos(atan(p.y,p.x)*2))
		discard;
	else 
		vFragColor = vColor;
	*/

	//rounded star shape	
	/*
	vec2 p = gl_PointCoord* 2.0 - vec2(1.0);
	float r = sqrt(dot(p,p));
	float theta = atan(p.y,p.x);
	if(dot(p,p) > 0.5*(exp(cos(theta*5)*0.75)) )
		discard;
	else 
		vFragColor = vColor;
	*/
}