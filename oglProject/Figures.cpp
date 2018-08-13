#include "Figures.h"

Figures::Figures(){}

//positions, textures
void Figures::Square20(GLfloat* vertices, const GLuint sizeVer, GLuint* indices, const GLuint sizeInd) {
	if (sizeVer == 20 && sizeInd == 6) {
		GLfloat* vertices_tmp = new float[20]{
			// positions          //texture coords
			-0.5f, -0.5f,  0.0f,  0.0f, 0.0f,
			0.5f, -0.5f,  0.0f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.0f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		};
		for (GLuint i = 0; i < sizeVer; ++i) vertices[i] = vertices_tmp[i];
		delete[] vertices_tmp;

		GLuint* indices_tmp = new GLuint[6]{
			0, 1, 2,
			0, 2, 3
		};
		for (GLuint i = 0; i < sizeInd; ++i) indices[i] = indices_tmp[i];
		delete[] indices_tmp;
	}
}

//positions
void Figures::Cube72(GLfloat* vertices, const GLuint sizeVer, GLuint* indices, const GLuint sizeInd) {
	if (sizeVer == 72 && sizeInd == 36) {
		GLfloat* vertices_tmp = new float[72]{
			-0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,

			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,

			 0.5f,  0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f, -0.5f,
		     0.5f,  0.5f, -0.5f,

			-0.5f, -0.5f, -0.5f,
		     0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,

			-0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f, -0.5f
		};
		for (GLuint i = 0; i < sizeVer; ++i) vertices[i] = vertices_tmp[i];
		delete[] vertices_tmp;

		GLuint* indices_tmp = new GLuint[36]{
			0, 1, 2,
			0, 2, 3,

			4, 5, 6,
			4, 6, 7,

			8, 9, 10,
			8, 10, 11,

			12, 13, 14,
			12, 14, 15,

			16, 17, 18,
			16, 18, 19,

			20, 21, 22,
			20, 22, 23
		};
		for (GLuint i = 0; i < sizeInd; ++i) indices[i] = indices_tmp[i];
		delete[] indices_tmp;
	}
}

//positions, textures
void Figures::Cube120(GLfloat* vertices, const GLuint sizeVer, GLuint* indices, const GLuint sizeInd) {
	if (sizeVer == 120 && sizeInd == 36) {
		GLfloat* vertices_tmp = new float[120]{
			// positions          //texture coords 
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f
		};
		for (GLuint i = 0; i < sizeVer; ++i) vertices[i] = vertices_tmp[i];
		delete[] vertices_tmp;

		GLuint* indices_tmp = new GLuint[36]{
			0, 1, 2,
			0, 2, 3, 

			4, 5, 6, 
			4, 6, 7,

			8, 9, 10,
			8, 10, 11,

			12, 13, 14, 
			12, 14, 15,

			16, 17, 18,
			16, 18, 19,

			20, 21, 22,
			20, 22, 23
		};
		for (GLuint i = 0; i < sizeInd; ++i) indices[i] = indices_tmp[i];
		delete[] indices_tmp;
	}
}

//positions, normals
void Figures::Cube144(GLfloat* vertices, const GLuint sizeVer, GLuint* indices, const GLuint sizeInd) {
	if (sizeVer == 144 && sizeInd == 36) {
		GLfloat* vertices_tmp = new float[144]{
			// positions          // normals 
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

			0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
		};
		for (GLuint i = 0; i < sizeVer; ++i) vertices[i] = vertices_tmp[i];
		delete[] vertices_tmp;

		GLuint* indices_tmp = new GLuint[36]{
			0, 1, 2,
			0, 2, 3,

			4, 5, 6,
			4, 6, 7,

			8, 9, 10,
			8, 10, 11,

			12, 13, 14,
			12, 14, 15,

			16, 17, 18,
			16, 18, 19,

			20, 21, 22,
			20, 22, 23
		};
		for (GLuint i = 0; i < sizeInd; ++i) indices[i] = indices_tmp[i];
		delete[] indices_tmp;
	}
}

//positions, textures (not indices)
void Figures::Cube180(GLfloat* vertices, const GLuint sizeVer) {
	if (sizeVer == 180) {
		GLfloat* vertices_tmp = new float[180]{
			// positions          // texture coords 
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			-0.5f, 0.5f, -0.5f,  0.0f, 1.0f,
			0.5f,  -0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f
		};
		for (GLuint i = 0; i < sizeVer; ++i) vertices[i] = vertices_tmp[i];
		delete[] vertices_tmp;
	}
}

//positions, normals, textures
void Figures::Cube192(GLfloat* vertices, const GLuint sizeVer, GLuint* indices, const GLuint sizeInd) {
	if (sizeVer == 192 && sizeInd == 36) {
		GLfloat* vertices_tmp = new float[192]{
			// positions          // normals			//texture coords
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,

			0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f
		};
		for (GLuint i = 0; i < sizeVer; ++i) vertices[i] = vertices_tmp[i];
		delete[] vertices_tmp;

		GLuint* indices_tmp = new GLuint[36]{
			0, 1, 2,
			0, 2, 3,

			4, 5, 6,
			4, 6, 7,

			8, 9, 10,
			8, 10, 11,

			12, 13, 14,
			12, 14, 15,

			16, 17, 18,
			16, 18, 19,

			20, 21, 22,
			20, 22, 23
		};
		for (GLuint i = 0; i < sizeInd; ++i) indices[i] = indices_tmp[i];
		delete[] indices_tmp;
	}
}


void Figures::BindVertexCube72(GLuint &VAO, GLuint &VBO, GLuint &EBO, GLfloat* vertices, GLsizeiptr sizeofVer, GLuint* indices, GLsizeiptr sizeofInd) {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeofVer, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeofInd, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

}

void Figures::BindVertexCube120(GLuint &VAO, GLuint &VBO, GLuint &EBO, GLfloat* vertices, GLsizeiptr sizeofVer, GLuint* indices, GLsizeiptr sizeofInd){
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeofVer, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeofInd, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	//glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void Figures::BindVertexCube144(GLuint &VAO, GLuint &VBO, GLuint &EBO, GLfloat* vertices, GLsizeiptr sizeofVer, GLuint* indices, GLsizeiptr sizeofInd) {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeofVer, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeofInd, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(3*sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void Figures::BindVertexLightCube72(GLuint & VAO, GLuint & VBO, GLuint & EBO, GLfloat * vertices, GLsizeiptr sizeofVer, GLuint * indices, GLsizeiptr sizeofInd){
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeofVer, vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeofInd, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void Figures::BindVertexLightCube144(GLuint &VAO, GLuint &VBO, GLuint &EBO, GLfloat* vertices, GLsizeiptr sizeofVer, GLuint* indices, GLsizeiptr sizeofInd) {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeofVer, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeofInd, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void Figures::BindVertexCube192(GLuint &VAO, GLuint &VBO, GLuint &EBO, GLfloat* vertices, GLsizeiptr sizeofVer, GLuint* indices, GLsizeiptr sizeofInd) {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeofVer, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeofInd, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void Figures::DeleteVertexCube(GLuint & VAO, GLuint & VBO, GLuint & EBO){
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
void Figures::DeleteVertexLightCube(GLuint & VAO, GLuint & VBO, GLuint & EBO){

}
