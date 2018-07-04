#pragma once
#ifndef MATERIALS_H
#define MATERIALS_H


#include <GLEW/glew.h>
#include <glm/glm.hpp>

class Materials
{
public:
	Materials();
	Materials(GLuint name);
	glm::vec3
		ambient,
		diffuse,
		specular;
	float shininess;
	GLuint name;
	void MakeMaterial(GLuint name);
private:
	enum names {
		emerald = 1,
		jade = 2,
		obsidian = 3,
		pearl = 4,
		ruby = 5,
		turquoise = 6,
		brass = 7,
		bronze = 8,
		chrome = 9,
		copper = 10,
		gold = 11,
		silver = 12,
		black_plastic = 13,
		cyan_plastic = 14,
		green_plastic = 15,
		red_plastic = 16,
		white_plastic = 17,
		yellow_plastic = 18,
		black_rubber = 19,
		cyan_rubber = 20,
		green_rubber = 21,
		red_rubber = 22,
		white_rubber = 23,
		yellow_rubber = 24
	};
	GLuint minName = 1;
	GLuint maxName = 24;
	GLuint checkLimitsEnum(GLuint name);
};

#endif 