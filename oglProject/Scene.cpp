#include "Scene.h"



Scene::Scene()
{
}

void Scene::DrawScene1(Camera& camera, GLFWwindow *window, const GLuint WIDTH, const GLuint HEIGHT, bool* keys) {
	camera.FPScam = true;
	Lamps 
		dirLamp(glm::vec3(1.2f, 50.0f, -20.0f), glm::vec3(1.0f, 0.98f, 0.75f)),
		pointLamp(glm::vec3(1.2f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
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
		simpleTexShader(simpleTexVertexPath, simpleTexFragmentPath),
		simpleTexGrassShader(simpleTexGrassVertexPath, simpleTexGrassFragmentPath),
		normalOutLineShader(normalOutLineVertexPath, normalOutLineFragmentPath),
		outLineShader(outLineVertexPath, outLineFragmentPath);
	Model 
		floor(floorPath),
		nanosuit(nanosuitPath),
		sphere(spherePath),
		cube(cubePath),
		windoW(windowPath),
		grass(grassPath);


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
			false
		);
		glEnable(GL_CULL_FACE);
		//grass
		glDisable(GL_CULL_FACE);
		for (float scaleX = -7.0f; scaleX <= -2.0f; scaleX += 0.8f) {
			for (float scaleZ = -7.0f; scaleZ <= 0.0f; scaleZ += 0.8f) {
				for (int angleY = 0; angleY < 180; angleY += 20) {
					grass.DrawTexModel(
						simpleTexGrassShader,
						glm::vec3(scaleX, -0.7f, scaleZ), 0, angleY, 0, glm::vec3(0.3f),
						view, projection, camera.Position, 64,
						modelLamps,
						false
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
			false
		);
		//pointLamps
		sphere.DrawColorModel(
			simpleShader,
			pointLamp.position, 0, 0, 0, glm::vec3(0.1f),
			view, projection,
			pointLamp.color,
			false
		);
		//cube
		//#1
		cube.DrawTexModel(
			textureShader,
			glm::vec3(1.0f, -0.699f, 0.0f), 0, 0, 0, glm::vec3(0.3f),
			view, projection, camera.Position, 64,
			modelLamps,
			false
		);
		//#2
		cube.DrawTexModel(
			textureShader,
			glm::vec3(2.0f, -0.699f, -1.0f), 0, 0, 0, glm::vec3(0.3f),
			view, projection, camera.Position, 64,
			modelLamps,
			false
		);
		//nanosuit
		nanosuit.DrawTexModel(
			textureShader,
			glm::vec3(0.0f, -1.0f, 0.0f), 0, 0, 0, glm::vec3(0.1f),
			view, projection, camera.Position, 64,
			modelLamps,
			true, &normalOutLineShader, glm::vec3(0.1f), 0.1f, glm::vec3(1.0f, 0.5f, 0.0f)
		);
		//windows
		std::map<float, glm::vec3> sorted;
		for (float scaleX = 0, scaleZ = 1; scaleX >= -2; scaleX -= 0.5f, scaleZ += 0.5f) {
			float distance = glm::length(camera.Position - glm::vec3(scaleX, -0.75f, scaleZ));
			sorted[distance] = glm::vec3(scaleX, -0.75f, scaleZ);
		}
		glDisable(GL_CULL_FACE);
		for (auto it = sorted.rbegin(); it != sorted.rend(); it++) {
			windoW.DrawTexModel(
				simpleTexShader,
				it->second, 0, 0, 0, glm::vec3(0.25f),
				view, projection, camera.Position, 64,
				modelLamps,
				false
			);
		}
		glEnable(GL_CULL_FACE);

		glfwSwapBuffers(window);
	}
}

void Scene::DrawScene2(Camera& camera, GLFWwindow *window, const GLuint WIDTH, const GLuint HEIGHT, bool* keys) {
	camera.FPScam = true;
	Lamps
		dirLamp(glm::vec3(1.2f, 50.0f, -20.0f), glm::vec3(1.0f, 0.98f, 0.75f)),
		pointLamp(glm::vec3(1.2f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
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
		simpleTexShader(simpleTexVertexPath, simpleTexFragmentPath),
		simpleTexGrassShader(simpleTexGrassVertexPath, simpleTexGrassFragmentPath),
		normalOutLineShader(normalOutLineVertexPath, normalOutLineFragmentPath),
		outLineShader(outLineVertexPath, outLineFragmentPath),
		frameSimpleTexShader(frameSimpleTexVertexPath, frameSimpleTexFragmentPath);
	Model
		floor(floorPath),
		nanosuit(nanosuitPath),
		sphere(spherePath),
		cube(cubePath),
		windoW(windowPath),
		grass(grassPath);

	//frames
	GLuint quadVAO, quadVBO;
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	GLuint framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	GLuint textureColorbuffer;
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

	GLuint rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
		
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		do_movement(camera, keys);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

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
			false
		);
		glEnable(GL_CULL_FACE);
		//grass
		glDisable(GL_CULL_FACE);
		for (float scaleX = -7.0f; scaleX <= -2.0f; scaleX += 0.8f) {
			for (float scaleZ = -7.0f; scaleZ <= 0.0f; scaleZ += 0.8f) {
				for (int angleY = 0; angleY < 180; angleY += 20) {
					grass.DrawTexModel(
						simpleTexGrassShader,
						glm::vec3(scaleX, -0.7f, scaleZ), 0, angleY, 0, glm::vec3(0.3f),
						view, projection, camera.Position, 64,
						modelLamps,
						false
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
			false
		);
		//pointLamps
		sphere.DrawColorModel(
			simpleShader,
			pointLamp.position, 0, 0, 0, glm::vec3(0.1f),
			view, projection,
			pointLamp.color,
			false
		);
		//cube
		//#1
		cube.DrawTexModel(
			textureShader,
			glm::vec3(1.0f, -0.699f, 0.0f), 0, 0, 0, glm::vec3(0.3f),
			view, projection, camera.Position, 64,
			modelLamps,
			false
		);
		//#2
		cube.DrawTexModel(
			textureShader,
			glm::vec3(2.0f, -0.699f, -1.0f), 0, 0, 0, glm::vec3(0.3f),
			view, projection, camera.Position, 64,
			modelLamps,
			false
		);
		//nanosuit
		nanosuit.DrawTexModel(
			textureShader,
			glm::vec3(0.0f, -1.0f, 0.0f), 0, 0, 0, glm::vec3(0.1f),
			view, projection, camera.Position, 64,
			modelLamps,
			true, &normalOutLineShader, glm::vec3(0.1f), 0.1f, glm::vec3(1.0f, 0.5f, 0.0f)
		);
		//windows
		std::map<float, glm::vec3> sorted;
		for (float scaleX = 0, scaleZ = 1; scaleX >= -2; scaleX -= 0.5f, scaleZ += 0.5f) {
			float distance = glm::length(camera.Position - glm::vec3(scaleX, -0.75f, scaleZ));
			sorted[distance] = glm::vec3(scaleX, -0.75f, scaleZ);
		}
		glDisable(GL_CULL_FACE);
		for (auto it = sorted.rbegin(); it != sorted.rend(); it++) {
			windoW.DrawTexModel(
				simpleTexShader,
				it->second, 0, 0, 0, glm::vec3(0.25f),
				view, projection, camera.Position, 64,
				modelLamps,
				false
			);
		}
		glEnable(GL_CULL_FACE);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		frameSimpleTexShader.Use();
		glBindVertexArray(quadVAO);
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &quadVAO);
	glDeleteBuffers(1, &quadVBO);
}

void Scene::DrawScene3(Camera& camera, GLFWwindow *window, const GLuint WIDTH, const GLuint HEIGHT, bool* keys) {
	camera.FPScam = true;
	Lamps
		dirLamp(glm::vec3(1.2f, 50.0f, -20.0f), glm::vec3(1.0f, 0.98f, 0.75f)),
		pointLamp(glm::vec3(1.2f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
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
		simpleTexShader(simpleTexVertexPath, simpleTexFragmentPath),
		simpleTexGrassShader(simpleTexGrassVertexPath, simpleTexGrassFragmentPath),
		normalOutLineShader(normalOutLineVertexPath, normalOutLineFragmentPath),
		outLineShader(outLineVertexPath, outLineFragmentPath);
	Model
		floor(floorPath),
		nanosuit(nanosuitPath),
		sphere(spherePath),
		cube(cubePath),
		windoW(windowPath),
		grass(grassPath);

	//cubeMap


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
			false
		);
		glEnable(GL_CULL_FACE);
		//grass
		glDisable(GL_CULL_FACE);
		for (float scaleX = -7.0f; scaleX <= -2.0f; scaleX += 0.8f) {
			for (float scaleZ = -7.0f; scaleZ <= 0.0f; scaleZ += 0.8f) {
				for (int angleY = 0; angleY < 180; angleY += 20) {
					grass.DrawTexModel(
						simpleTexGrassShader,
						glm::vec3(scaleX, -0.7f, scaleZ), 0, angleY, 0, glm::vec3(0.3f),
						view, projection, camera.Position, 64,
						modelLamps,
						false
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
			false
		);
		//pointLamps
		sphere.DrawColorModel(
			simpleShader,
			pointLamp.position, 0, 0, 0, glm::vec3(0.1f),
			view, projection,
			pointLamp.color,
			false
		);
		//cube
		//#1
		cube.DrawTexModel(
			textureShader,
			glm::vec3(1.0f, -0.699f, 0.0f), 0, 0, 0, glm::vec3(0.3f),
			view, projection, camera.Position, 64,
			modelLamps,
			false
		);
		//#2
		cube.DrawTexModel(
			textureShader,
			glm::vec3(2.0f, -0.699f, -1.0f), 0, 0, 0, glm::vec3(0.3f),
			view, projection, camera.Position, 64,
			modelLamps,
			false
		);
		//nanosuit
		nanosuit.DrawTexModel(
			textureShader,
			glm::vec3(0.0f, -1.0f, 0.0f), 0, 0, 0, glm::vec3(0.1f),
			view, projection, camera.Position, 64,
			modelLamps,
			true, &normalOutLineShader, glm::vec3(0.1f), 0.1f, glm::vec3(1.0f, 0.5f, 0.0f)
		);
		//windows
		std::map<float, glm::vec3> sorted;
		for (float scaleX = 0, scaleZ = 1; scaleX >= -2; scaleX -= 0.5f, scaleZ += 0.5f) {
			float distance = glm::length(camera.Position - glm::vec3(scaleX, -0.75f, scaleZ));
			sorted[distance] = glm::vec3(scaleX, -0.75f, scaleZ);
		}
		glDisable(GL_CULL_FACE);
		for (auto it = sorted.rbegin(); it != sorted.rend(); it++) {
			windoW.DrawTexModel(
				simpleTexShader,
				it->second, 0, 0, 0, glm::vec3(0.25f),
				view, projection, camera.Position, 64,
				modelLamps,
				false
			);
		}
		glEnable(GL_CULL_FACE);

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
