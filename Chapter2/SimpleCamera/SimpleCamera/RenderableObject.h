#pragma once
#include "GLSLShader.h"

class RenderableObject
{
public:
	RenderableObject(void);
	virtual ~RenderableObject(void);
	virtual void Render(const float* MVP)=0;

protected:
	GLuint vaoID;
	GLuint vboVerticesID;
	GLuint vboIndicesID;
	int total_indices; 
	GLSLShader shader;
};

