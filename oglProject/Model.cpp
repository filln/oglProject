#include "Model.h"

Model::Model(const char* path){
	loadModel(path);
}

void Model::Draw(Shader& shader) {
	for (GLuint i = 0; i < this->meshes.size(); i++)
		meshes[i].Draw(shader);
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
		//if (type == aiTextureType_DIFFUSE)  texture.type = "texture_diffuse";
		//if (type == aiTextureType_SPECULAR) texture.type = "texture_specular";

		bool skip = false;
		if(this->textures_loaded.size())
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
	cout << filename << endl;
	GLuint texture;
	glGenTextures(1, &texture);
	cout << texture << endl;
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

	int texWidth, texHeight, nrComponents = 3;
	unsigned char* image = SOIL_load_image(filename.c_str(), &texWidth, &texHeight, 0, SOIL_LOAD_RGB);
//	unsigned char* image = stbi_load(filename.c_str(), &texWidth, &texHeight, &nrComponents, 0);
	if (image) {

		GLenum format;
		if (nrComponents == 1) format = GL_RED;
		if (nrComponents == 3) format = GL_RGB;
		if (nrComponents == 4) format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, format, texWidth, texHeight, 0, format, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		SOIL_free_image_data(image);
//		stbi_image_free(image);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else {
		cout << "Failed to load image: " << path << endl;
		SOIL_free_image_data(image);
//		stbi_image_free(image);
	}
	return texture;
}

Model::~Model()
{
}
