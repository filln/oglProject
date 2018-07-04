#pragma once

#include <glm/glm.hpp>
#include <GLEW/glew.h>
#include <string>
#include <vector>
#include "shader.h"

using std::string; 
using std::to_string;
using std::vector;

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};
struct TexTypes {
	string
		material = "material.",
		diffuse = "texture_diffuse",
		specular = "texture_specular";
};
struct Texture {
	GLuint id;
	string type;
	string path;
};

class Mesh
{
public:
	GLuint VAO;
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
	Mesh(const vector<Vertex>& vertices, const vector<GLuint>& indices, const vector<Texture>& textures);
	void Draw(Shader& shader) const;
	~Mesh();
private:
	TexTypes texTypes;
	GLuint VBO, EBO;
	void setupMesh();
};

