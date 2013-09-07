#pragma once
#include "renderableobject.h"
class CScreenSizeQuad :
	public RenderableObject
{
public:
	CScreenSizeQuad(void);
	virtual ~CScreenSizeQuad(void);

	void Render(const float* MVP);
};

