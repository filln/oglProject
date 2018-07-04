#include "Camera.h"



Camera::Camera():
	Position(glm::vec3(0.0f, 0.0f, 3.0f)),
	WorldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
	Yaw(YAW),
	Pitch(PITCH),
	Speed(SPEED),
	Sensitivity(SENSITIVITY),
	Zoom(ZOOM),
	FPScam(false)
{
	this->updateCameraVectors();
}
Camera::Camera(
	glm::vec3 position,
	glm::vec3 worldup,
	GLfloat yaw,
	GLfloat pitch, 
	GLfloat speed,
	GLfloat sensitivity,
	GLfloat zoom
) : FPScam(false)
{
	this->Position = position;
	this->WorldUp = worldup;
	this->Yaw = yaw;
	this->Pitch = pitch;
	this->Speed = speed;
	this->Sensitivity = sensitivity;
	this->Zoom = zoom;
	this->updateCameraVectors();
}

//Camera::Camera(
//	GLfloat posX,
//	GLfloat posY,
//	GLfloat posZ,
//	GLfloat upX,
//	GLfloat upY,
//	GLfloat upZ,
//	GLfloat yaw,
//	GLfloat pitch, 
//	GLfloat speed,
//	GLfloat sensitivity,
//	GLfloat zoom
//) 
//{
//	this->Position = glm::vec3(posX, posY, posZ);
//	this->WorldUp = glm::vec3(upX, upY, upZ);
//	this->Yaw = yaw;
//	this->Pitch = pitch;
//	this->updateCameraVectors();
//}

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime) {
	GLfloat velocity = this->Speed * deltaTime;
	if (direction == FORWARD) {
		if (this->FPScam)
			this->Position += this->FrontFPScam * velocity;
		else
			this->Position += this->Front * velocity;
	}
	if (direction == BACKWARD) {
		if (this->FPScam)
			this->Position -= this->FrontFPScam * velocity;
		else
			this->Position -= this->Front * velocity;
	}
	if (direction == LEFT) this->Position -= this->Right * velocity;
	if (direction == RIGHT) this->Position += this->Right * velocity;
	if (direction == UP) this->Position += this->Up * velocity;
	if (direction == DOWN) this->Position -= this->Up * velocity;
}

void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch) {
	xoffset *= Sensitivity;
	yoffset *= Sensitivity;
	this->Yaw += xoffset;
	this->Pitch += yoffset;
	if (constrainPitch) {
		if (this->Pitch > 89.0f) this->Pitch = 89.0f;
		if (this->Pitch < -89.0f) this->Pitch = -89.0f;
	}
	this->updateCameraVectors();
}

void Camera::ProcessMouseScroll(GLfloat yoffset) {
	if (this->Zoom >= 1.0f && this->Zoom <= 45.0f) this->Zoom -= yoffset;
	if (this->Zoom <= 1.0f) this->Zoom = 1.0f;
	if (this->Zoom >= 45.0f) this->Zoom = 45.0f;
}

void Camera::updateCameraVectors() {
	glm::vec3 front;
	front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
	front.y = sin(glm::radians(this->Pitch));
	front.z = cos(glm::radians(this->Pitch)) * sin(glm::radians(this->Yaw));
	if (this->FPScam) {
		glm::vec3 frontFPScam;
		frontFPScam.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(PITCH));
		frontFPScam.y = sin(glm::radians(PITCH));
		frontFPScam.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(PITCH));
		this->FrontFPScam = glm::normalize(frontFPScam);
	}
	this->Front = glm::normalize(front);
	this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));
	this->Up = glm::normalize(glm::cross(this->Right, this->Front));
}