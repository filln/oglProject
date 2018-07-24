#include "SkyBox.h"



SkyBox::SkyBox()
{
}

SkyBox::SkyBox(
	const char* positiveX, const char* negativeX,
	const char* positiveY, const char* negativeY,
	const char* positiveZ, const char* negativeZ
) {
	faces[0] = positiveX;	faces[1] = negativeX;
	faces[2] = positiveY;   faces[3] = negativeY;
	faces[4] = positiveZ;   faces[5] = negativeZ;

	cubemapTexture = loadCubemap(faces);
}

void SkyBox::DrawSky(
	Shader& shader,
	glm::vec3 scale,
	glm::mat4 view, glm::mat4 projection
) {

}

GLuint SkyBox::loadCubemap(const char* faces[]) {
	GLuint	sizeFaces = sizeof(faces) / sizeof(const char*);
	if (sizeFaces != 6) {
		std::cout << "size of faces[] for cubemap must be 6" << std::endl;
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

	return texture;
}

SkyBox::~SkyBox()
{
}
