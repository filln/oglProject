#include "Mesh.h"

Mesh::Mesh(const vector<Vertex>& vertices, const vector<GLuint>& indices, const vector<Texture>& textures)
	:
		vertices(vertices),
		indices(indices),
		textures(textures)
{
	setupMesh();
}

void Mesh::setupMesh() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	//vertex positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	//normal positions
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(1);
	//texture positions
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
} 
void Mesh::Draw(Shader& shader) const {
	if (this->textures.size()) {
		GLuint 
			diffuseNr = 1, 
			specularNr = 1;
		for (GLuint i = 0; i < this->textures.size(); ++i) {
			glActiveTexture(GL_TEXTURE0 + i);

			string
				number,
				name = this->textures[i].type;

			if (name == this->texTypes.diffuse) 
				number = to_string(diffuseNr++);
			if (name == this->texTypes.specular) 
				number = to_string(specularNr++);

			shader.setInt((texTypes.material + name + number).c_str(), i);
			//if (name == "texture_diffuse")
			//	number = to_string(diffuseNr++);
			//if (name == "texture_specular")
			//	number = to_string(specularNr++);

			//shader.setInt(("material." + name + number).c_str(), i);

			glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
		}
	}
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}

Mesh::~Mesh()
{
}
