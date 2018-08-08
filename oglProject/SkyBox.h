#pragma once

#include <stb/stb_image.h>
#include "shader.h"

class SkyBox
{
public:
	SkyBox();
	SkyBox(
		const GLchar* positiveX, const GLchar* negativeX,
		const GLchar* positiveY, const GLchar* negativeY,
		const GLchar* positiveZ, const GLchar* negativeZ
	);
	void DrawSky(
		Shader& shader, 
		glm::mat4 view, glm::mat4 projection
	);
	GLuint GetTexture() const;
	~SkyBox();
private:
	const GLchar* faces[6];
	GLfloat	vertices[72] = {
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,

		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,

		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f
	};
	GLuint indices[36] = {
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	};
	GLuint 
		texture,
		VAO, VBO, EBO,
		loadCubemap(const GLchar* faces[], GLuint sizeFaces = 6);
};

