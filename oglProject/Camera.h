#ifndef CAMERA_H
#define CAMERA_H

#pragma once

#include <GLEW/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT, 
	UP,
	DOWN
};
const GLfloat 
	YAW = -90.0f,
	PITCH = 0.0f,
	SPEED = 3.0f,
	SENSITIVITY = 0.15f,
	ZOOM = 45.0f;

class Camera
{
public:
	glm::vec3
		Position,
		Front,
		FrontFPScam,
		Up,
		Right,
		WorldUp;
	GLfloat
		Yaw,
		Pitch,
		Speed,
		Sensitivity,
		Zoom;
	GLboolean FPScam;

	Camera();
	Camera(
		glm::vec3 position,
		glm::vec3 worldup,
		GLfloat yaw,
		GLfloat pitch, 
		GLfloat speed,
		GLfloat sensitivity,
		GLfloat zoom
	);
	//Camera(
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
	//);
	glm::mat4 GetViewMatrix();
	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);
	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset,	GLboolean constrainPitch);
	void ProcessMouseScroll(GLfloat yoffset);

private:
	void updateCameraVectors();
};

#endif //CAMERA_H