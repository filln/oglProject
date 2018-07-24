#pragma once
#ifndef SHADER_H
#define SHADER_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glm/gtc/type_ptr.hpp>
#include "Lamps.h"
#include "Camera.h"

using std::string;
using std::to_string;

class Shader
{
public:
	GLuint Program;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void Use();
	void setInt(const GLchar* chName, GLint name);
	void setFloat(const GLchar* chName, float name);
	void setVec3(const GLchar* chName, glm::vec3 name);
	void setMat4(const GLchar* chName, glm::mat4 name);
	void setDirLamps(Lamps* lamps, const GLuint lampsCount);
	void setPointLamps(Lamps* lamps, const GLuint lampsCount);
	void setSpotLamps(Lamps* lamps, const GLuint lampsCount);
	~Shader();
private:
	string
		dirLampsCount = "dirLampsCount",
		pointLampsCount = "pointLampsCount",
		spotLampsCount = "spotLampsCount",
		dirLights = "dirLights[",
		pointLights = "pointLights[",
		spotLights = "spotLights[",
		direction = "].direction",
		position = "].position",
		ambient = "].ambient",
		diffuse = "].diffuse",
		specular = "].specular",
		constant = "].constant",
		linear = "].linear",
		quadratic = "].quadratic",
		cutOff = "].cutOff",
		outerCutOff = "].outerCutOff";
};

#endif

