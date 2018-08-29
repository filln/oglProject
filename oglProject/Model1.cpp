#include "Model.h"

//without outline&lamps
void Model::DrawTexModel(
	Shader& shader,
	glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale
) {
	glm::mat4 model;
	model = glm::translate(model, translate);
	if (angleX)	model = glm::rotate(model, glm::radians(angleX), glm::vec3(1.0f, 0.0f, 0.0f));
	if (angleY)	model = glm::rotate(model, glm::radians(angleY), glm::vec3(0.0f, 1.0f, 0.0f));
	if (angleZ)	model = glm::rotate(model, glm::radians(angleZ), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, scale);

	shader.Use();
	shader.setMat4("model", model);
	this->Draw(shader);
}

//without outline
//with textures
void Model::DrawTexModel(
	Shader& shader,
	glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale,
	glm::vec3 viewPos, GLint shininessTex,
	ModelLamps& modelLamps
) {
	glm::mat4 model;
	model = glm::translate(model, translate);
	if (angleX)	model = glm::rotate(model, glm::radians(angleX), glm::vec3(1.0f, 0.0f, 0.0f));
	if (angleY)	model = glm::rotate(model, glm::radians(angleY), glm::vec3(0.0f, 1.0f, 0.0f));
	if (angleZ)	model = glm::rotate(model, glm::radians(angleZ), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, scale);

	shader.Use();
	shader.setMat4("model", model);
	shader.setVec3("viewPos", viewPos);
	//Materials
	shader.setFloat("material.shininessTex", shininessTex);
	if (modelLamps.dirLamps)	shader.setDirLamps(modelLamps.dirLamps, modelLamps.dirLampsCount);
	if (modelLamps.pointLamps)	shader.setPointLamps(modelLamps.pointLamps, modelLamps.pointLampsCount);
	if (modelLamps.spotLamps)	shader.setSpotLamps(modelLamps.spotLamps, modelLamps.spotLampsCount);
	this->Draw(shader);
}
//with users color
void Model::DrawColorModel(
	Shader& shader,
	glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale,
	glm::vec3 inColor
) {
	glm::mat4 model;
	model = glm::translate(model, translate);
	if (angleX)	model = glm::rotate(model, glm::radians(angleX), glm::vec3(1.0f, 0.0f, 0.0f));
	if (angleY)	model = glm::rotate(model, glm::radians(angleY), glm::vec3(0.0f, 1.0f, 0.0f));
	if (angleZ)	model = glm::rotate(model, glm::radians(angleZ), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, scale);

	shader.Use();
	shader.setMat4("model", model);
	shader.setVec3("inColor", inColor);
	this->Draw(shader);
}
//with material
void Model::DrawMatModel(
	Materials& material,
	Shader& shader,
	glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale,
	glm::vec3 viewPos,
	ModelLamps& modelLamps
) {
	glm::mat4 model;
	model = glm::translate(model, translate);
	if (angleX)	model = glm::rotate(model, glm::radians(angleX), glm::vec3(1.0f, 0.0f, 0.0f));
	if (angleY)	model = glm::rotate(model, glm::radians(angleY), glm::vec3(0.0f, 1.0f, 0.0f));
	if (angleZ)	model = glm::rotate(model, glm::radians(angleZ), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, scale);

	shader.Use();
	shader.setMat4("model", model);
	shader.setVec3("viewPos", viewPos);
	//Materials
	shader.setInt("inIsTex", 0);
	shader.setVec3("material.ambient", material.ambient);
	shader.setVec3("material.diffuse", material.diffuse);
	shader.setVec3("material.specular", material.specular);
	shader.setFloat("material.shininess", material.shininess);
	if (modelLamps.dirLamps)	shader.setDirLamps(modelLamps.dirLamps, modelLamps.dirLampsCount);
	if (modelLamps.pointLamps)	shader.setPointLamps(modelLamps.pointLamps, modelLamps.pointLampsCount);
	if (modelLamps.spotLamps)	shader.setSpotLamps(modelLamps.spotLamps, modelLamps.spotLampsCount);
	this->Draw(shader);
}