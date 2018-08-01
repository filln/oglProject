#include "Model.h"

Model::Model(const char* path) {
	loadModel(path);
}

void Model::Draw(Shader& shader) {
	for (GLuint i = 0; i < this->meshes.size(); i++)
		meshes[i].Draw(shader);
}
//without outline
//with textures
void Model::DrawTexModel(
	Shader& shader,
	glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale,
	glm::mat4 view, glm::mat4 projection, glm::vec3 viewPos, GLint shininessTex,
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
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
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
	glm::mat4 view, glm::mat4 projection,
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
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
	shader.setVec3("inColor", inColor);
	this->Draw(shader);
}
//with material
void Model::DrawMatModel(
	Materials& material,
	Shader& shader,
	glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale,
	glm::mat4 view, glm::mat4 projection, glm::vec3 viewPos,
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
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
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
//with outline
	//with textures
void Model::DrawTexModel(
	Shader& shader,
	glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale,
	glm::mat4 view, glm::mat4 projection, glm::vec3 viewPos, GLint shininessTex,
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
			view, projection, viewPos, shininessTex,
			modelLamps
		);
		if (shaderOutLine) {
			glStencilFunc(GL_NOTEQUAL, 1, 1);
			glStencilMask(0);
			glDisable(GL_DEPTH_TEST);
			this->drawOutLineModel(
				shaderOutLine,
				translate, angleX, angleY, angleZ, scaleOutLine,
				view, projection,
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
			view, projection, viewPos, shininessTex,
			modelLamps
		);
	}
	glStencilMask(1);
}
	//with users color
void Model::DrawColorModel(
	Shader& shader,
	glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale,
	glm::mat4 view, glm::mat4 projection,
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
			view, projection,
			inColor
		);
		if (shaderOutLine) {
			glStencilFunc(GL_NOTEQUAL, 1, 1);
			glStencilMask(0);
			glDisable(GL_DEPTH_TEST);
			this->drawOutLineModel(
				shaderOutLine,
				translate, angleX, angleY, angleZ, scaleOutLine,
				view, projection,
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
			view, projection,
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
	glm::mat4 view, glm::mat4 projection, glm::vec3 viewPos,
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
			view, projection, viewPos,
			modelLamps
		);
		if (shaderOutLine) {
			glStencilFunc(GL_NOTEQUAL, 1, 1);
			glStencilMask(0);
			glDisable(GL_DEPTH_TEST);
			this->drawOutLineModel(
				shaderOutLine,
				translate, angleX, angleY, angleZ, scaleOutLine,
				view, projection,
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
			view, projection, viewPos,
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
	glm::mat4 view, glm::mat4 projection, glm::vec3 viewPos, GLint shininessTex,
	ModelLamps& modelLamps,
	GLboolean isOutLine
) {
	if (!isOutLine) {
		this->DrawTexModel(
			shader,
			translate, angleX, angleY, angleZ, scale,
			view, projection, viewPos, shininessTex,
			modelLamps,
			isOutLine, nullptr, glm::vec3(0), 0, glm::vec3(0)
		);
	}
}
		//with users color
void Model::DrawColorModel(
	Shader& shader,
	glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale,
	glm::mat4 view, glm::mat4 projection,
	glm::vec3 inColor,
	GLboolean isOutLine
) {
	if (!isOutLine) {
		this->DrawColorModel(
			shader,
			translate, angleX, angleY, angleZ, scale,
			view, projection,
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
	glm::mat4 view, glm::mat4 projection, glm::vec3 viewPos,
	ModelLamps& modelLamps,
	GLboolean isOutLine
) {
	if (!isOutLine) {
		this->DrawMatModel(
			material,
			shader,
			translate, angleX, angleY, angleZ, scale,
			view, projection, viewPos,
			modelLamps,
			isOutLine, nullptr, glm::vec3(0), 0, glm::vec3(0)
		);
	}
}
//outline with color
void Model::drawOutLineModel(
	Shader* shaderOutLine,
	glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scaleOutLine,
	glm::mat4 view, glm::mat4 projection,
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
		shaderOutLine->setMat4("view", view);
		shaderOutLine->setMat4("projection", projection);
		shaderOutLine->setVec3("inColor", inColorOutLine);
		shaderOutLine->setFloat("rate", rateOutLine);
		this->Draw(*shaderOutLine);
	}
}
//outline with material

//mirrorModel
void Model::DrawMirrorModel(
	Shader& shader,
	glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale,
	glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPosition,
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
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
	shader.setVec3("cameraPosition", cameraPosition);
	this->Draw(shader);
}
void Model::loadModel(string path) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
		cin.get();
		return;
	}
	this->directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene) {
	for (GLuint i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	for (GLuint i = 0; i < node->mNumChildren; i++)
		processNode(node->mChildren[i], scene);
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	for (GLuint i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;

		glm::vec3 Position;
		Position.x = mesh->mVertices[i].x;
		Position.y = mesh->mVertices[i].y;
		Position.z = mesh->mVertices[i].z;
		vertex.Position = Position;
		glm::vec3 Normal;
		Normal.x = mesh->mNormals[i].x;
		Normal.y = mesh->mNormals[i].y;
		Normal.z = mesh->mNormals[i].z;
		vertex.Normal = Normal;
		if (mesh->mTextureCoords[0]) {
			glm::vec2 TexCoords;
			TexCoords.x = mesh->mTextureCoords[0][i].x;
			TexCoords.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = TexCoords;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	for (GLuint i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}


	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type) {
	vector<Texture> textures;
	for (GLuint i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		Texture texture;
		mat->GetTexture(type, i, &str);
		texture.path = string(str.C_Str());
		if (type == aiTextureType_DIFFUSE)  texture.type = this->texTypes.diffuse;
		if (type == aiTextureType_SPECULAR) texture.type = this->texTypes.specular;

		bool skip = false;
		if (this->textures_loaded.size())
			for (GLuint j = 0; j < this->textures_loaded.size(); j++)
				if (!std::strcmp(this->textures_loaded[j].path.c_str(), str.C_Str())) {
					texture.id = this->textures_loaded[j].id;
					skip = true;
					break;
				}
		if (!skip) {
			texture.id = TextureFromFile(str.C_Str(), this->directory);
			this->textures_loaded.push_back(texture);
		}
		textures.push_back(texture);
	}
	return textures;
}

GLuint TextureFromFile(const char* path, const string& directory) {
	string filename = string(path);
	filename = directory + "/" + filename;
	GLuint texture;
	glGenTextures(1, &texture);

	//	cout << filename << endl;
	//	cout << texture << endl;

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//
	int
		texWidth, texHeight,
		nrComponents;
	//unsigned char* image = SOIL_load_image(filename.c_str(), &texWidth, &texHeight, 0, SOIL_LOAD_RGB);
	unsigned char* image = stbi_load(filename.c_str(), &texWidth, &texHeight, &nrComponents, 0);
	if (image) {

		GLenum format;
		if (nrComponents == 1) format = GL_RED;
		if (nrComponents == 3) format = GL_RGB;
		if (nrComponents == 4) format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, format, texWidth, texHeight, 0, format, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		//if (format == GL_RGBA) {
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		//}
		//else {
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//		SOIL_free_image_data(image);
		stbi_image_free(image);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else {
		cout << "Failed to load image: " << path << endl;
		//		SOIL_free_image_data(image);
		stbi_image_free(image);
	}
	return texture;
}

Model::~Model()
{
}
