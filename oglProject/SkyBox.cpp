#include "SkyBox.h"



SkyBox::SkyBox()
{
}

SkyBox::SkyBox(
	const GLchar* positiveX, const GLchar* negativeX,
	const GLchar* positiveY, const GLchar* negativeY,
	const GLchar* positiveZ, const GLchar* negativeZ
) {
	faces[0] = positiveX;	faces[1] = negativeX;
	faces[2] = positiveY;   faces[3] = negativeY;
	faces[4] = positiveZ;   faces[5] = negativeZ;

	texture = loadCubemap(faces);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesFull), verticesFull, GL_STATIC_DRAW);
//	std::cout << sizeof(indices) / sizeof(float) << std::endl;
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SkyBox::DrawSky(
	Shader& shader,
	glm::vec3 scale,
	glm::mat4 view, glm::mat4 projection
) {
	glDepthMask(GL_FALSE);
	glDisable(GL_CULL_FACE);

	shader.Use();
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);

	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	glEnable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);
}

GLuint SkyBox::loadCubemap(const char* faces[], GLuint sizeFaces) {
	if (sizeFaces != 6) {
		std::cout << "size of faces[] for cubemap must be 6" << std::endl;
		std::cout << "sizeFaces == "<< sizeFaces << std::endl;
		return 0;
	}

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	int
		texWidth, texHeight,
		nrComponents;
	for (GLuint i = 0; i < sizeFaces; i++) {
		unsigned char* image = stbi_load(faces[i], &texWidth, &texHeight, &nrComponents, 0);
		if (image) {
			GLenum format;
			if (nrComponents == 1) format = GL_RED;
			if (nrComponents == 3) format = GL_RGB;
			if (nrComponents == 4) format = GL_RGBA;
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, format, texWidth, texHeight, 0, format, GL_UNSIGNED_BYTE, image
			);
			stbi_image_free(image);
		}
		else {
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(image);
			return 0;
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

//	std::cout << texture << std::endl;
	return texture;
}

SkyBox::~SkyBox()
{
}
