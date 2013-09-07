#pragma once
#include "abstractcamera.h"

class CFreeCamera :
	public CAbstractCamera
{
public:
	CFreeCamera(void);
	~CFreeCamera(void);

	void Update();
	void Rotate(const float yaw, const float pitch, const float roll);
	void Walk(const float amount);
	void Strafe(const float amount);
	void Lift(const float amount);
	 

protected:
	float yaw, pitch, roll;
	
	glm::vec3 translation;
};

