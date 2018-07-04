#pragma once
#ifndef LAMPS_H
#define LAMPS_H


#include <GLEW/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <cmath>

class Lamps
{
public:
	Lamps();
	glm::vec3
		direction,
		position,
		firstPosition,

		color,
		ambient,
		diffuse,
		specular;
	GLuint	distance;
	float
		constant,
		linear,
		quadratic,
		cutOff,
		outerCutOff,
		ambientStrength;
	static const GLuint
		countPositions = 10,
		countColors = 10;
	glm::vec3 positions[countPositions] = {
		glm::vec3(1.2f, 1.0f, 1.0f),
		glm::vec3(1.6f, 1.4f, 0.6f),
		glm::vec3(1.8f, 1.6f, 0.4f),
		glm::vec3(1.6f, 2.0f, 0.0f),
		glm::vec3(1.2f, 1.6f, -0.4f),
		glm::vec3(0.8f, 1.2f, -0.8f),
		glm::vec3(0.4f, 0.8f, -0.6f),
		glm::vec3(0.0f, 0.4f, -0.4f),
		glm::vec3(-0.4f, 0.0f, -0.2f),
		glm::vec3(0.0f, 0.4f, -0.1f)
	};
	glm::vec3 colors[countColors] = {
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(0.51f, 0.24f, 0.46f),
		glm::vec3(0.44f, 0.24f, 0.51f),
		glm::vec3(0.24f, 0.26f, 0.51f),
		glm::vec3(0.24f, 0.44f, 0.51f),
		glm::vec3(0.20f, 0.74f, 0.63f),
		glm::vec3(0.20f, 0.74f, 0.24f),
		glm::vec3(0.82f, 0.87f, 0.11f),
		glm::vec3(0.87f, 0.56f, 0.11f),
		glm::vec3(0.54f, 0.11f, 0.87f)
	};
	void Rotate(glm::vec3 position);
	void SetDistance(GLuint distance);
	void SetColors();
	~Lamps();
};

#endif 