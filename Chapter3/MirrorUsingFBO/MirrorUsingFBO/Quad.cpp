#include "Quad.h"
#include <glm/glm.hpp>
 
CQuad::CQuad(float zpos)
{
	//generate the cube object
	shader.LoadFromFile(GL_VERTEX_SHADER, "shaders/quad_shader.vert");
	shader.LoadFromFile(GL_FRAGMENT_SHADER, "shaders/quad_shader.frag");
	shader.CreateAndLinkProgram();
	shader.Use();
		shader.AddAttribute("vVertex"); 
		shader.AddAttribute("vUV");  
		shader.AddUniform("MVP"); 
		shader.AddUniform("textureMap"); 
		glUniform1i(shader("textureMap"), 0);
	shader.UnUse();
	Zpos = zpos;

	Init();
}


CQuad::~CQuad(void)
{
}

int CQuad::GetTotalVertices() {
	return 4;
}

int CQuad::GetTotalIndices() {
	return 6;
}

GLenum CQuad::GetPrimitiveType() {
	return GL_TRIANGLES;
}

void CQuad::FillVertexBuffer(GLfloat* pBuffer) {
	glm::vec3* vertices = (glm::vec3*)(pBuffer); 
	vertices[0] = glm::vec3( -1,0, Zpos);
	vertices[1] = glm::vec3( 1, 0, Zpos);
	vertices[2] = glm::vec3( 1, 2, Zpos);
	vertices[3] = glm::vec3( -1, 2, Zpos); 
		 
	glm::vec3 center = vertices[0];
	center += vertices[1];
	center += vertices[2];
	center += vertices[3];
	position.x = center.x/4.0f;
	position.y = center.y/4.0f;
	position.z = center.z/4.0f;

	glm::vec3 e1 = vertices[1]-vertices[0];
	glm::vec3 e2 = vertices[2]-vertices[0];
	normal  = glm::cross(e1,e2); 
}

void CQuad::FillIndexBuffer(GLuint* pBuffer) {
	//fill indices array
	GLuint* id=pBuffer; 
	*id++ = 0; 
	*id++ = 1; 
	*id++ = 2;
	*id++ = 0;  
	*id++ = 2;  
	*id++ = 3;  
}