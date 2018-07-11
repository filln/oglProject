#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "Model.h"
#include "Camera.h"
//#include "Materials.h"
#include "Lamps.h"

class Scene
{
public:
	Scene();
	void DrawScene1(Camera& camera);
	~Scene();
private:
	const GLchar
		*nanosuitPath = "tex/nanosuit/nanosuit.obj",
		*earthPath = "tex/earth/earth.obj",
		*spherePath = "tex/sphere.blend",
		*cubePath = "tex/container/cube.obj",
		*floorPath = "tex/floor/floor.blend",

		*textureVertexPath = "shaders/textures.vs",
		*textureFragmentPath = "shaders/textures.fs",
		*lampSphereVertexPath = "shaders/lampSphere.vs",
		*lampSphereFragmentPath = "shaders/lampSphere.fs",
		*simpleVertexPath = "shaders/simple.vs",
		*simpleFragmentPath = "shaders/simple.fs",
		*normalOutLineVertexPath = "shaders/normalOutLine.vs",
		*normalOutLineFragmentPath = "shaders/normalOutLine.fs",
		*outLineVertexPath = "shaders/outLine.vs",
		*outLineFragmentPath = "shaders/outLine.fs";
	void do_movement(Camera& camera);
};

