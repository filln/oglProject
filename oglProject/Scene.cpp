#include "Scene.h"



Scene::Scene()
{
}

void Scene::DrawScene1(Camera& camera, GLFWwindow *window, const GLuint WIDTH, const GLuint HEIGHT, bool* keys) {
	const GLchar
		*nanosuitPath = "tex/nanosuit/nanosuit.obj",
		*earthPath = "tex/earth/earth.obj",
		*spherePath = "tex/sphere.blend",
		*cubePath = "tex/container/cube.obj",
		*floorPath = "tex/floor/floor.obj",
		*grassPath = "tex/grass/grass.blend",

		*textureVertexPath = "shaders/textures.vs",
		*textureFragmentPath = "shaders/textures.fs",
		*lampSphereVertexPath = "shaders/lampSphere.vs",
		*lampSphereFragmentPath = "shaders/lampSphere.fs",
		*simpleVertexPath = "shaders/simple.vs",
		*simpleFragmentPath = "shaders/simple.fs",
		*simpleTexGrassVertexPath = "shaders/simpleTexGrass.vs",
		*simpleTexGrassFragmentPath = "shaders/simpleTexGrass.fs",
		*normalOutLineVertexPath = "shaders/normalOutLine.vs",
		*normalOutLineFragmentPath = "shaders/normalOutLine.fs",
		*outLineVertexPath = "shaders/outLine.vs",
		*outLineFragmentPath = "shaders/outLine.fs";

	camera.FPScam = true;
	Lamps dirLamp(glm::vec3(1.2f, 50.0f, -20.0f), glm::vec3(1.0f, 0.98f, 0.75f));
	Lamps pointLamp(glm::vec3(1.2f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelLamps modelLamps;
	modelLamps.dirLamps = &dirLamp;
	modelLamps.dirLampsCount = 1;
	modelLamps.pointLamps = &pointLamp;
	modelLamps.pointLampsCount = 1;
	modelLamps.spotLamps = nullptr;
	modelLamps.spotLampsCount = 0;

	Shader
		textureShader(textureVertexPath, textureFragmentPath),
		lampSphereShader(lampSphereVertexPath, lampSphereFragmentPath),
		simpleShader(simpleVertexPath, simpleFragmentPath),
		simpleTexGrassShader(simpleTexGrassVertexPath, simpleTexGrassFragmentPath),
		normalOutLineShader(normalOutLineVertexPath, normalOutLineFragmentPath),
		outLineShader(outLineVertexPath, outLineFragmentPath);
	Model floor(floorPath);
	Model nanosuit(nanosuitPath);
	Model sphere(spherePath);
	Model cube(cubePath);
	Model grass(grassPath);


	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		do_movement(camera, keys);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_STENCIL_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glStencilMask(0);
		glm::mat4 view, projection;
		view = camera.GetViewMatrix();
		projection = glm::perspective(glm::radians(camera.Zoom), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
		//floor
		glDisable(GL_CULL_FACE);
		floor.DrawTexModel(
			textureShader,
			glm::vec3(0.0f, -1.0f, 0.0f), 0, 0, 0, glm::vec3(1.0f),
			view, projection, camera.Position, 64,
			modelLamps,
			false, nullptr, glm::vec3(0), 0, glm::vec3(0)
		);
		glEnable(GL_CULL_FACE);
		//grass
		glDisable(GL_CULL_FACE);
		for (float scaleX = -7.0f; scaleX <= -2.0f; scaleX += 0.8f) {
			for (float scaleZ = -7.0f; scaleZ <= 7.0f; scaleZ += 0.8f) {
				for (int angleY = 0; angleY < 180; angleY += 20) {
					grass.DrawTexModel(
						simpleTexGrassShader,
						glm::vec3(scaleX, -0.7f, scaleZ), 0, angleY, 0, glm::vec3(0.3f),
						view, projection, camera.Position, 64,
						modelLamps,
						false, nullptr, glm::vec3(0), 0, glm::vec3(0)
					);
				}
			}
		}
		glEnable(GL_CULL_FACE);
		//dirLamps
		sphere.DrawColorModel(
			simpleShader,
			dirLamp.position, 0, 0, 0, glm::vec3(1.0f),
			view, projection,
			dirLamp.color,
			false, nullptr, glm::vec3(0), 0, glm::vec3(0)
		);
		//pointLamps
		sphere.DrawColorModel(
			simpleShader,
			pointLamp.position, 0, 0, 0, glm::vec3(0.1f),
			view, projection,
			pointLamp.color,
			false, nullptr, glm::vec3(0), 0, glm::vec3(0)
		);
		//cube
		//#1
		cube.DrawTexModel(
			textureShader,
			glm::vec3(1.0f, -0.699f, 0.0f), 0, 0, 0, glm::vec3(0.3f),
			view, projection, camera.Position, 64,
			modelLamps,
			false, nullptr, glm::vec3(0), 0, glm::vec3(0)
		);
		//#2
		cube.DrawTexModel(
			textureShader,
			glm::vec3(2.0f, -0.699f, -1.0f), 0, 0, 0, glm::vec3(0.3f),
			view, projection, camera.Position, 64,
			modelLamps,
			false, nullptr, glm::vec3(0), 0, glm::vec3(0)
		);
		//nanosuit
		nanosuit.DrawTexModel(
			textureShader,
			glm::vec3(0.0f, -1.0f, 0.0f), 0, 0, 0, glm::vec3(0.1f),
			view, projection, camera.Position, 64,
			modelLamps,
			true, &normalOutLineShader, glm::vec3(0.1f), 0.1f, glm::vec3(1.0f, 0.5f, 0.0f)
		);


		glfwSwapBuffers(window);
	}
}

void Scene::do_movement(Camera& camera, bool* keys) {
	GLfloat currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	if (keys[GLFW_KEY_W]) camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S]) camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A]) camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D]) camera.ProcessKeyboard(RIGHT, deltaTime);
	if (keys[GLFW_KEY_SPACE]) camera.ProcessKeyboard(UP, deltaTime);
	if (keys[GLFW_KEY_LEFT_SHIFT]) camera.ProcessKeyboard(DOWN, deltaTime);
}
Scene::~Scene()
{
}
