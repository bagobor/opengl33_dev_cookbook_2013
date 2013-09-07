#include "FreeCamera.h"


CFreeCamera::CFreeCamera()
{
	translation =glm::vec3(0);
}


CFreeCamera::~CFreeCamera(void)
{
}
 
void CFreeCamera::Update() {
	glm::mat4 R = GetMatrixUsingYawPitchRoll(yaw,pitch,roll); 
	position+=translation;
	translation=glm::vec3(0);

	look = glm::vec3(R*glm::vec4(0,0,1,0));
	glm::vec3 tgt  = position+look;
	up   = glm::vec3(R*glm::vec4(0,1,0,0));
	right = glm::cross(look, up);
	V = glm::lookAt(position, tgt, up);

	//normalize
	//look = glm::normalize(look);
	//up = glm::normalize(up);
	//right = glm::normalize(right);
}

void CFreeCamera::Rotate(const float y, const float p, const float r) {
	yaw=y;
	pitch=p;
	roll=r;
}


void CFreeCamera::Walk(const float amount) {
	translation += (look*amount);
}

void CFreeCamera::Strafe(const float amount) {
	translation += (right*amount);
}

void CFreeCamera::Lift(const float amount) {
	translation += (up*amount);
}