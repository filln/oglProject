#pragma once

#include "shader.h"
#include "Model.h"
#include "Camera.h"
#include "Lamps.h"
#include "SkyBox.h"
#include <map>

class Scene
{
public:
	Scene();
	//default
	void DrawScene1(Camera& camera, GLFWwindow *window, const GLuint WIDTH, const GLuint HEIGHT, bool* keys);
	//framebuffer
	void DrawScene2(Camera& camera, GLFWwindow *window, const GLuint WIDTH, const GLuint HEIGHT, bool* keys);
	//skybox
	void DrawScene3(Camera& camera, GLFWwindow *window, const GLuint WIDTH, const GLuint HEIGHT, bool* keys);
	~Scene();
private:
	GLfloat
		deltaTime = 0.0f,
		lastFrame = 0.0f,
		//for Scene2
		quadVertices[24] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		 // positions  // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};
	const GLchar
		//models
		*nanosuitPath = "tex/nanosuit/nanosuit.obj",
		*earthPath = "tex/earth/earth.obj",
		*spherePath = "tex/sphere.blend",
		*semispherePath = "tex/semisphere.blend",
		*cubePath = "tex/container/cube.obj",
		*floorPath = "tex/floor/floor.obj",
		*grassPath = "tex/grass/grass.blend",
		*windowPath = "tex/window/window.blend",
		//shaders
		*textureVertexPath = "shaders/textures.vs",
		*textureFragmentPath = "shaders/textures.fs",
		*lampSphereVertexPath = "shaders/lampSphere.vs",
		*lampSphereFragmentPath = "shaders/lampSphere.fs",
		*simpleVertexPath = "shaders/simple.vs",
		*simpleFragmentPath = "shaders/simple.fs",
		*simpleTexVertexPath = "shaders/simpleTex.vs",
		*simpleTexFragmentPath = "shaders/simpleTex.fs",
		*simpleTexGrassVertexPath = "shaders/simpleTexGrass.vs",
		*simpleTexGrassFragmentPath = "shaders/simpleTexGrass.fs",
		*normalOutLineVertexPath = "shaders/normalOutLine.vs",
		*normalOutLineFragmentPath = "shaders/normalOutLine.fs",
		*outLineVertexPath = "shaders/outLine.vs",
		*outLineFragmentPath = "shaders/outLine.fs",
		//for Scene2
		*frameSimpleTexVertexPath = "shaders/frameSimpleTex.vs",
		*frameSimpleTexFragmentPath = "shaders/frameSimpleTex.fs",
		//for Scene3
			//shaders
		*skyVertexPath = "shaders/skyBox.vs",
		*skyFragmentPath = "shaders/skyBox.fs",
		*skyMirrorVertexPath = "shaders/skyMirror.vs",
		*skyMirrorFragmentPath = "shaders/skyMirror.fs",
		*skyPrismVertexPath = "shaders/skyPrism.vs",
		*skyPrismFragmentPath = "shaders/skyPrism.fs",
			//textures
		*right = "tex/skybox/right.jpg",
		*left = "tex/skybox/left.jpg",
		*top = "tex/skybox/top.jpg",
		*bottom = "tex/skybox/bottom.jpg",
		*front = "tex/skybox/front.jpg",
		*back = "tex/skybox/back.jpg";


	void do_movement(Camera& camera, bool* keys);
};

