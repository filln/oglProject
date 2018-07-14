#pragma once

#include <GLEW/glew.h>
//#include <SOIL/SOIL.h>
//#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <vector>
#include <iostream>
#include "Shader.h"
#include "Lamps.h"
#include "Materials.h"
#include "Mesh.h"

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

GLuint TextureFromFile(const char* path, const string& directory);
struct ModelLamps {
	Lamps* dirLamps; GLuint dirLampsCount;
	Lamps* pointLamps; GLuint pointLampsCount;
	Lamps* spotLamps; GLuint spotLampsCount;
};
class Model
{
public:
	Model(const char* path);
	void Draw(Shader& shader);
	//without outline
		//with textures
	void DrawTexModel(
		Shader& shader,
		glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale,
		glm::mat4 view, glm::mat4 projection, glm::vec3 viewPos, GLint shininessTex,
		ModelLamps& modelLamps
	);
		//with users color
	void DrawColorModel(
		Shader& shader,
		glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale,
		glm::mat4 view, glm::mat4 projection,
		glm::vec3 inColor
	);
		//with material
	void DrawMatModel(
		Materials& material,
		Shader& shader,
		glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale,
		glm::mat4 view, glm::mat4 projection, glm::vec3 viewPos,
		ModelLamps& modelLamps
	);
	//with outline
		//with textures
	void DrawTexModel(
		Shader& shader,
		glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale,
		glm::mat4 view, glm::mat4 projection, glm::vec3 viewPos, GLint shininessTex,
		ModelLamps& modelLamps,
		GLboolean isOutLine, Shader* shaderOutLine, glm::vec3 scaleOutLine, GLfloat rateOutLine, glm::vec3 inColorOutLine
	);
		//with users color
	void DrawColorModel(
		Shader& shader,
		glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale,
		glm::mat4 view, glm::mat4 projection,
		glm::vec3 inColor,
		GLboolean isOutLine, Shader* shaderOutLine, glm::vec3 scaleOutLine, GLfloat rateOutLine, glm::vec3 inColorOutLine
	);
		//with material
	void DrawMatModel(
		Materials& material,
		Shader& shader,
		glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale,
		glm::mat4 view, glm::mat4 projection, glm::vec3 viewPos,
		ModelLamps& modelLamps,
		GLboolean isOutLine, Shader* shaderOutLine, glm::vec3 scaleOutLine, GLfloat rateOutLine, glm::vec3 inColorOutLine
	);
		//disable outline
			//with textures
	void DrawTexModel(
		Shader& shader,
		glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale,
		glm::mat4 view, glm::mat4 projection, glm::vec3 viewPos, GLint shininessTex,
		ModelLamps& modelLamps,
		GLboolean isOutLine
	);
			//with users color
	void DrawColorModel(
		Shader& shader,
		glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale,
		glm::mat4 view, glm::mat4 projection,
		glm::vec3 inColor,
		GLboolean isOutLine
	);
			//with material
	void DrawMatModel(
		Materials& material,
		Shader& shader,
		glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scale,
		glm::mat4 view, glm::mat4 projection, glm::vec3 viewPos,
		ModelLamps& modelLamps,
		GLboolean isOutLine
	);
	~Model();
private:
	TexTypes texTypes;
	vector<Mesh> meshes;
	vector<Texture> textures_loaded;
	string directory;
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type);
	void drawOutLineModel(
		Shader* shaderOutLine,
		glm::vec3 translate, GLfloat angleX, GLfloat angleY, GLfloat angleZ, glm::vec3 scaleOutLine,
		glm::mat4 view, glm::mat4 projection,
		glm::vec3 inColorOutLine,
		GLfloat rateOutLine
	);
};

