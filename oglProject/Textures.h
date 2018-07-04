#ifndef TEXTURES_H
#define TEXTURES_H

#pragma once

#include <GLEW/glew.h>
#include <SOIL/SOIL.h>
class Textures
{
public:
	Textures();
	GLuint CreateTexture2D(const GLchar* texturePath);
};

#endif 
