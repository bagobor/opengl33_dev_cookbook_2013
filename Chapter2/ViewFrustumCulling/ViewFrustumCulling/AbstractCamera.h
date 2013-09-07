#pragma once
#include "Plane.h"
#include <glm/gtc/matrix_transform.hpp>

class CAbstractCamera
{
public:
	CAbstractCamera(void);
	~CAbstractCamera(void);
	 
	void SetupProjection(const float fovy, const float aspectRatio, const float near, const float far);
	
	virtual void Update() = 0;
	virtual void Rotate(const float yaw, const float pitch, const float roll) = 0;
	//virtual void Translate(const float dx, const float dy, const float dz) = 0;

	const glm::mat4 GetViewMatrix() const;
	const glm::mat4 GetProjectionMatrix() const;

	void SetPosition(const glm::vec3& v);
	const glm::vec3 GetPosition() const;

	glm::mat4 GetMatrixUsingYawPitchRoll(const float yaw, const float pitch, const float roll);

	void SetFOV(const float fov);
	const float GetFOV() const;
	const float GetAspectRatio() const; 
	
	
	void CalcFrustumPlanes();
	bool IsPointInFrustum(const glm::vec3& point);
	bool IsSphereInFrustum(const glm::vec3& center, const float radius);
	bool IsBoxInFrustum(const glm::vec3& min, const glm::vec3& max);
	 

	//frustum points
	glm::vec3 farPts[4];
	glm::vec3 nearPts[4];

	void GetFrustumPlanes(glm::vec4 planes[6]);

protected:	 

	float fov, aspect_ratio, Znear, Zfar;
	static glm::vec3 UP;
	glm::vec3 look;
	glm::vec3 up;
	glm::vec3 right; 
	glm::vec3 position;
	glm::mat4 V; //view matrix
	glm::mat4 P; //projection matrix

	//Frsutum planes
	CPlane planes[6];

};

