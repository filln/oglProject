#pragma once

#include <GLEW/glew.h>
#include <SOIL/SOIL.h>
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb/stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <vector>
#include <iostream>
#include "Shader.h"
#include "Mesh.h"

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

GLuint TextureFromFile(const char* path, const string& directory);
class Model
{
public:
	Model(const char* path);
	void Draw(Shader& shader);
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
};

