#ifndef FIGURES_H
#define FIGURES_H

#pragma once

#include <GLEW/glew.h>

class Figures
{
public:
	Figures();

	void Square20(GLfloat* vertices, const GLuint sizeVer, GLuint* indices, const GLuint sizeInd);
	void Cube72(GLfloat* vertices, const GLuint sizeVer, GLuint* indices, const GLuint sizeInd);
	void Cube144(GLfloat* vertices, const GLuint sizeVer, GLuint* indices, const GLuint sizeInd);
	void Cube120(GLfloat* vertices, const GLuint sizeVer, GLuint* indices, const GLuint sizeInd);
	void Cube180(GLfloat* vertices, const GLuint sizeVer);
	void Cube192(GLfloat* vertices, const GLuint sizeVer, GLuint* indices, const GLuint sizeInd);

	void BindVertexCube72(GLuint &VAO, GLuint &VBO, GLuint &EBO, GLfloat* vertices, GLsizeiptr sizeofVer, GLuint* indices, GLsizeiptr sizeofInd);
	void BindVertexCube144(GLuint &VAO, GLuint &VBO, GLuint &EBO, GLfloat* vertices, GLsizeiptr sizeofVer, GLuint* indices, GLsizeiptr sizeofInd);
	void BindVertexCube120(GLuint &VAO, GLuint &VBO, GLuint &EBO, GLfloat* vertices, GLsizeiptr sizeofVer, GLuint* indices, GLsizeiptr sizeofInd);
	void BindVertexCube192(GLuint &VAO, GLuint &VBO, GLuint &EBO, GLfloat* vertices, GLsizeiptr sizeofVer, GLuint* indices, GLsizeiptr sizeofInd);
	void BindVertexLightCube72(GLuint &VAO, GLuint &VBO, GLuint &EBO, GLfloat* vertices, GLsizeiptr sizeofVer, GLuint* indices, GLsizeiptr sizeofInd);
	void BindVertexLightCube144(GLuint &VAO, GLuint &VBO, GLuint &EBO, GLfloat* vertices, GLsizeiptr sizeofVer, GLuint* indices, GLsizeiptr sizeofInd);

	void DeleteVertexCube(GLuint &VAO, GLuint &VBO, GLuint &EBO);
	void DeleteVertexLightCube(GLuint &VAO, GLuint &VBO, GLuint &EBO);
};

#endif