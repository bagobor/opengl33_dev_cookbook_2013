#include "AbstractCamera.h" 
#include <glm/gtc/quaternion.hpp>

#include <glm/gtx/quaternion.hpp>

glm::vec3 CAbstractCamera::UP = glm::vec3(0,1,0);

CAbstractCamera::CAbstractCamera(void) 
{ 
}


CAbstractCamera::~CAbstractCamera(void)
{
}

void CAbstractCamera::SetupProjection(const float fovy, const float aspRatio) {
	P = glm::perspective(fovy, aspRatio, 0.1f, 1000.0f); 
	fov = fovy;
	aspect_ratio = aspRatio;
} 

const glm::mat4 CAbstractCamera::GetViewMatrix() const {
	return V;
}

const glm::mat4 CAbstractCamera::GetProjectionMatrix() const {
	return P;
}

const glm::vec3 CAbstractCamera::GetPosition() const {
	return position;
}

void CAbstractCamera::SetPosition(const glm::vec3 p) {
	position = p;
}
 
glm::mat4 CAbstractCamera::GetMatrixUsingYawPitchRoll(const float yaw, const float pitch, const float roll) {
	 
	glm::mat4 R=glm::mat4(1);
	
	R = glm::rotate(R, roll, glm::vec3(0,0,1));
	R = glm::rotate(R,  yaw, glm::vec3(0,1,0));
	R = glm::rotate(R, pitch, glm::vec3(1,0,0));
	
	return R;
}

const float CAbstractCamera::GetFOV() const {
	return fov;
} 

const float CAbstractCamera::GetAspectRatio() const {
	return aspect_ratio;
}

 