#include "Model.h"

//mirrorModel
void Model::DrawMirrorModel(
	Shader& shader,
	glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale,
	glm::vec3 cameraPosition,
	GLuint skyboxTexture
) {
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);

	glm::mat4 model;
	model = glm::translate(model, translate);
	if (angleX)	model = glm::rotate(model, glm::radians(angleX), glm::vec3(1.0f, 0.0f, 0.0f));
	if (angleY)	model = glm::rotate(model, glm::radians(angleY), glm::vec3(0.0f, 1.0f, 0.0f));
	if (angleZ)	model = glm::rotate(model, glm::radians(angleZ), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, scale);

	shader.Use();
	shader.setMat4("model", model);
	shader.setVec3("cameraPosition", cameraPosition);
	this->Draw(shader);
}

//prismModel
void Model::DrawPrismModel(
	Shader& shader,
	glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale,
	glm::vec3 cameraPosition,
	GLuint skyboxTexture,
	GLfloat material1, GLfloat material2
) {
	/*
	material	coeff.
	air			1.0
	water		1.33
	ice			1.309
	glass		1.52
	diamond		2.42
	*/

	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);

	glm::mat4 model;
	model = glm::translate(model, translate);
	if (angleX)	model = glm::rotate(model, glm::radians(angleX), glm::vec3(1.0f, 0.0f, 0.0f));
	if (angleY)	model = glm::rotate(model, glm::radians(angleY), glm::vec3(0.0f, 1.0f, 0.0f));
	if (angleZ)	model = glm::rotate(model, glm::radians(angleZ), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, scale);

	shader.Use();
	shader.setMat4("model", model);
	shader.setVec3("cameraPosition", cameraPosition);
	shader.setFloat("material1", material1);
	shader.setFloat("material2", material2);
	this->Draw(shader);
}