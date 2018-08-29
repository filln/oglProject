#include "Model.h"

//with outline
//with textures
void Model::DrawTexModel(
	Shader& shader,
	glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale,
	glm::vec3 viewPos, GLint shininessTex,
	ModelLamps& modelLamps,
	GLboolean isOutLine, Shader* shaderOutLine, glm::vec3 scaleOutLine, GLfloat rateOutLine, glm::vec3 inColorOutLine
) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	if (isOutLine) {
		glStencilFunc(GL_ALWAYS, 1, 1);
		glStencilMask(1);
		this->DrawTexModel(
			shader,
			translate, angleX, angleY, angleZ, scale,
			viewPos, shininessTex,
			modelLamps
		);
		if (shaderOutLine) {
			glStencilFunc(GL_NOTEQUAL, 1, 1);
			glStencilMask(0);
			glDisable(GL_DEPTH_TEST);
			this->drawOutLineModel(
				shaderOutLine,
				translate, angleX, angleY, angleZ, scaleOutLine,
				inColorOutLine,
				rateOutLine
			);
			glEnable(GL_DEPTH_TEST);
		}
	}
	else {
		glStencilFunc(GL_ALWAYS, 0, 1);
		glStencilMask(0);
		this->DrawTexModel(
			shader,
			translate, angleX, angleY, angleZ, scale,
			viewPos, shininessTex,
			modelLamps
		);
	}
	glStencilMask(1);
}
//with users color
void Model::DrawColorModel(
	Shader& shader,
	glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale,
	glm::vec3 inColor,
	GLboolean isOutLine, Shader* shaderOutLine, glm::vec3 scaleOutLine, GLfloat rateOutLine, glm::vec3 inColorOutLine
) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	if (isOutLine) {
		glStencilFunc(GL_ALWAYS, 1, 1);
		glStencilMask(1);
		this->DrawColorModel(
			shader,
			translate, angleX, angleY, angleZ, scale,
			inColor
		);
		if (shaderOutLine) {
			glStencilFunc(GL_NOTEQUAL, 1, 1);
			glStencilMask(0);
			glDisable(GL_DEPTH_TEST);
			this->drawOutLineModel(
				shaderOutLine,
				translate, angleX, angleY, angleZ, scaleOutLine,
				inColorOutLine,
				rateOutLine
			);
			glEnable(GL_DEPTH_TEST);
		}
	}
	else {
		glStencilFunc(GL_ALWAYS, 0, 1);
		glStencilMask(0);
		this->DrawColorModel(
			shader,
			translate, angleX, angleY, angleZ, scale,
			inColor
		);
	}
	glStencilMask(1);
}
//with material
void Model::DrawMatModel(
	Materials& material,
	Shader& shader,
	glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale,
	glm::vec3 viewPos,
	ModelLamps& modelLamps,
	GLboolean isOutLine, Shader* shaderOutLine, glm::vec3 scaleOutLine, GLfloat rateOutLine, glm::vec3 inColorOutLine
) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	if (isOutLine) {
		glStencilFunc(GL_ALWAYS, 1, 1);
		glStencilMask(1);
		this->DrawMatModel(
			material,
			shader,
			translate, angleX, angleY, angleZ, scale,
			viewPos,
			modelLamps
		);
		if (shaderOutLine) {
			glStencilFunc(GL_NOTEQUAL, 1, 1);
			glStencilMask(0);
			glDisable(GL_DEPTH_TEST);
			this->drawOutLineModel(
				shaderOutLine,
				translate, angleX, angleY, angleZ, scaleOutLine,
				inColorOutLine,
				rateOutLine
			);
			glEnable(GL_DEPTH_TEST);
		}
	}
	else {
		glStencilFunc(GL_ALWAYS, 0, 1);
		glStencilMask(0);
		this->DrawMatModel(
			material,
			shader,
			translate, angleX, angleY, angleZ, scale,
			viewPos,
			modelLamps
		);
	}
	glStencilMask(1);
}
//disable outline
//with textures
void Model::DrawTexModel(
	Shader& shader,
	glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale,
	glm::vec3 viewPos, GLint shininessTex,
	ModelLamps& modelLamps,
	GLboolean isOutLine
) {
	if (!isOutLine) {
		this->DrawTexModel(
			shader,
			translate, angleX, angleY, angleZ, scale,
			viewPos, shininessTex,
			modelLamps,
			isOutLine, nullptr, glm::vec3(0), 0, glm::vec3(0)
		);
	}
}
//with users color
void Model::DrawColorModel(
	Shader& shader,
	glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale,
	glm::vec3 inColor,
	GLboolean isOutLine
) {
	if (!isOutLine) {
		this->DrawColorModel(
			shader,
			translate, angleX, angleY, angleZ, scale,
			inColor,
			isOutLine, nullptr, glm::vec3(0), 0, glm::vec3(0)
		);
	}
}
//with material
void Model::DrawMatModel(
	Materials& material,
	Shader& shader,
	glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale,
	glm::vec3 viewPos,
	ModelLamps& modelLamps,
	GLboolean isOutLine
) {
	if (!isOutLine) {
		this->DrawMatModel(
			material,
			shader,
			translate, angleX, angleY, angleZ, scale,
			viewPos,
			modelLamps,
			isOutLine, nullptr, glm::vec3(0), 0, glm::vec3(0)
		);
	}
}
//outline with color
void Model::drawOutLineModel(
	Shader* shaderOutLine,
	glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scaleOutLine,
	glm::vec3 inColorOutLine,
	GLfloat rateOutLine
) {
	glm::mat4 model;
	model = glm::translate(model, translate);
	if (angleX)	model = glm::rotate(model, glm::radians(angleX), glm::vec3(1.0f, 0.0f, 0.0f));
	if (angleY)	model = glm::rotate(model, glm::radians(angleY), glm::vec3(0.0f, 1.0f, 0.0f));
	if (angleZ)	model = glm::rotate(model, glm::radians(angleZ), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, scaleOutLine);
	if (shaderOutLine) {
		shaderOutLine->Use();
		shaderOutLine->setMat4("model", model);
		shaderOutLine->setVec3("inColor", inColorOutLine);
		shaderOutLine->setFloat("rate", rateOutLine);
		this->Draw(*shaderOutLine);
	}
}
//outline with material
