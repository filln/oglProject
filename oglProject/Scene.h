#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "Model.h"
#include "Camera.h"
//#include "Materials.h"
#include "Lamps.h"
#include <map>

class Scene
{
public:
	Scene();
	void DrawScene1(Camera& camera, GLFWwindow *window, const GLuint WIDTH, const GLuint HEIGHT, bool* keys);
	void DrawScene2(Camera& camera, GLFWwindow *window, const GLuint WIDTH, const GLuint HEIGHT, bool* keys);
	~Scene();
private:
	GLfloat
		deltaTime = 0.0f,
		lastFrame = 0.0f;
	void do_movement(Camera& camera, bool* keys);
};

