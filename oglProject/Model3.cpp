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

//grassModel
void Model::GenerateGrass(
	const GLuint amount,
	glm::mat4 *modelMatrices,
	float limitXRight, float limitZRight,
	float y,
	float lgthX, float lgthZ,
	GLuint bufferGrass
) {
	modelMatrices = new glm::mat4[amount];
	srand(glfwGetTime());
	float
		x, z,
		rotateAngle;
	for (GLuint i = 0; i < amount; i++) {
		glm::mat4 model;
		if ((limitXRight - lgthX) < 0)
			x = (rand() % (int)(lgthX * 100)) * -1 / 100.0f + limitXRight;
		else
			x = (rand() % (int)(lgthX * 100)) / 100.0f + limitXRight;
		if ((limitZRight - lgthZ) < 0)
			z = (rand() % (int)(lgthZ * 100)) * -1 / 100.0f + limitZRight;
		else
			z = (rand() % (int)(lgthZ * 100)) / 100.0f + limitZRight;

		model = glm::translate(model, glm::vec3(x, y, z));

		rotateAngle = (float)((rand() % (180 * 100)) / 100);
		glm::vec3 rotateVec = glm::vec3(0.0f, 1.0f, 0.0f);
		model = glm::rotate(model, rotateAngle, rotateVec);

		glm::vec3 scaleVec = glm::vec3(0.3f);
		model = glm::scale(model, scaleVec);

		modelMatrices[i] = model;
	}

	glGenBuffers(1, &bufferGrass);
	glBindBuffer(GL_ARRAY_BUFFER, bufferGrass);
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), modelMatrices, GL_STATIC_DRAW);
	for (GLuint i = 0; i < this->meshes.size(); i++) {
		glBindVertexArray(this->meshes[i].VAO);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), nullptr);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)sizeof(glm::vec4));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);

		glBindVertexArray(0);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}
void Model::DrawGrassModel(
	Shader& shader,
	const GLuint amount
) {
	glDisable(GL_CULL_FACE);
	shader.Use();
	shader.setInt("material.texture_diffuse1", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->textures_loaded[0].id);
	for (GLuint i = 0; i < this->meshes.size(); i++) {
		glBindVertexArray(this->meshes[i].VAO);
		glDrawElementsInstanced(GL_TRIANGLES, this->meshes[i].indices.size(), GL_UNSIGNED_INT, 0, amount);
		glBindVertexArray(0);
	}
	glEnable(GL_CULL_FACE);
}