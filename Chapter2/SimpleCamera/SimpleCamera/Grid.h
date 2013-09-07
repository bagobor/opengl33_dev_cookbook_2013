#pragma once
#include "RenderableObject.h"

class CGrid:public RenderableObject
{
public:
	CGrid(int width=10, int depth=10);
	virtual ~CGrid(void);

	void Render(const float* MVP);
};

