#define GLEW_STATIC
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include "shader.h"
#include "Model.h"
#include "Camera.h"
//#include "Textures.h"
//#include "Figures.h"
//#include "Materials.h"
#include "Lamps.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void do_movement();

const GLchar
*nanosuitPath = "tex/nanosuit/nanosuit.obj",
*nanosuitVertexPath = "shaders/nanosuit.vs",
*nanosuitFragmentPath = "shaders/nanosuit.fs",

*earthPath = "tex/earth/earth.obj",

*spherePath = "tex/sphere.blend",
*lampSphereVertexPath = "shaders/lampSphere.vs",
*lampSphereFragmentPath = "shaders/lampSphere.fs",

*cubePath = "tex/container/cube.obj",
*floorPath = "tex/floor/floor.obj",

*outLineVertexPath = "shaders/outLine.vs",
*outLineFragmentPath = "shaders/outLine.fs";

Camera camera;

bool keys[1024];

float interpol = 0.2;
//const GLuint WIDTH = 800, HEIGHT = 600;
//const GLuint WIDTH = 1920, HEIGHT = 1080;
const GLuint WIDTH = 1024, HEIGHT = 768;

GLfloat
deltaTime = 0.0f, lastFrame = 0.0f,
lastX = (GLfloat)WIDTH / 2, lastY = (GLfloat)HEIGHT / 2;

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		system("pause");
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(window, (GLfloat)WIDTH / 2, (GLfloat)HEIGHT / 2);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		system("pause");
		return -2;
	}
	std::cout << glGetString(GL_VERSION) << std::endl;

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	camera.FPScam = true;
	const GLuint countPoints = 1;
	if (countPoints > 10) return 0;
	Lamps pointLamps[countPoints];
	if (countPoints > pointLamps[0].countPositions || pointLamps[0].countPositions != pointLamps[0].countColors) {
		cout << "must be (countPoints <= pointLamps[0].countPositions) && (pointLamps[0].countPositions == pointLamps[0].countColors)" << endl;
		cin.get();
		return 0;
	}
	for (GLuint i = 0; i < countPoints; i++) {
		pointLamps[i].position = pointLamps[i].positions[i];
		pointLamps[i].firstPosition = pointLamps[i].positions[i];
		pointLamps[i].color = pointLamps[i].colors[i];
		pointLamps[i].SetColors();
	}
	Lamps dirLamp;
	Shader
		nanosuitShader(nanosuitVertexPath, nanosuitFragmentPath),
		lampSphereShader(lampSphereVertexPath, lampSphereFragmentPath),
		outLineShader(outLineVertexPath, outLineFragmentPath);
	Model nanosuit(nanosuitPath);
	Model sphere(spherePath);
	dirLamp.direction = glm::vec3(1.2f, 50.0f, -20.0f);
	dirLamp.color = glm::vec3(1.0f, 0.98f, 0.75f);
	dirLamp.SetColors();
	Model cube(cubePath);
	Model floor(floorPath);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		do_movement();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glStencilMask(1);
		glm::mat4 view, projection;
		view = camera.GetViewMatrix();
		projection = glm::perspective(glm::radians(camera.Zoom), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
		//nanosuit
		glm::mat4 modelNanosuit;
		modelNanosuit = glm::translate(modelNanosuit, glm::vec3(1.1f, -1.0f, 0.3f));
		modelNanosuit = glm::scale(modelNanosuit, glm::vec3(0.1f, 0.1f, 0.1f));
		nanosuitShader.Use();
		nanosuitShader.setMat4("model", modelNanosuit);
		nanosuitShader.setMat4("view", view);
		nanosuitShader.setMat4("projection", projection);
		nanosuitShader.setVec3("viewPos", camera.Position);
		nanosuitShader.setFloat("material.shininessTex", 16);
		nanosuitShader.setPointLights(pointLamps, countPoints);
		nanosuitShader.setDirLights(&dirLamp, 1);
		nanosuit.Draw(nanosuitShader);
		//floor
		glm::mat4 modelFloor;
		modelFloor = glm::translate(modelFloor, glm::vec3(0.0f, -1.0f, 0.3f));
		modelFloor = glm::scale(modelFloor, glm::vec3(1.0f, 1.0f, 1.0f));
		nanosuitShader.Use();
		nanosuitShader.setMat4("model", modelFloor);
		nanosuitShader.setFloat("material.shininessTex", 512);
		floor.Draw(nanosuitShader);
		//pointLamps
		glm::mat4 modelLampSphere;
		lampSphereShader.Use();
		lampSphereShader.setMat4("view", view);
		lampSphereShader.setMat4("projection", projection);
		for (GLuint i = 0; i < countPoints; i++) {
			modelLampSphere = glm::mat4();
			modelLampSphere = glm::translate(modelLampSphere, pointLamps[i].position);
			modelLampSphere = glm::scale(modelLampSphere, glm::vec3(0.1f, 0.1f, 0.1f));
			lampSphereShader.setMat4("model", modelLampSphere);
			lampSphereShader.setVec3("inColor", pointLamps[i].color);
			sphere.Draw(lampSphereShader);
		}
		//dirLamps
		modelLampSphere = glm::mat4();
		modelLampSphere = glm::translate(modelLampSphere, dirLamp.direction);
		lampSphereShader.Use();
		lampSphereShader.setMat4("model", modelLampSphere);
		lampSphereShader.setVec3("inColor", dirLamp.color);
		sphere.Draw(lampSphereShader);
		//cube
		glStencilFunc(GL_ALWAYS, 1, 1);
		glStencilMask(0);
			//#1
		glm::mat4 modelCube;
		modelCube = glm::translate(modelCube, glm::vec3(2.1f, -0.695f, 0.3f));
		modelCube = glm::scale(modelCube, glm::vec3(0.3f, 0.3f, 0.3f));
		nanosuitShader.Use();
		nanosuitShader.setMat4("model", modelCube);
		nanosuitShader.setFloat("material.shininessTex", 128);
		cube.Draw(nanosuitShader);
			//#2
		modelCube = glm::mat4();
		modelCube = glm::translate(modelCube, glm::vec3(3.0f, -0.695f, -0.7f));
		modelCube = glm::scale(modelCube, glm::vec3(0.3f, 0.3f, 0.3f));
		nanosuitShader.Use();
		nanosuitShader.setMat4("model", modelCube);
		cube.Draw(nanosuitShader);
		//outLine
		glStencilFunc(GL_NOTEQUAL, 0, 1);
		glStencilMask(1);
		glDisable(GL_DEPTH_TEST);
			//#1
		modelCube = glm::mat4();
		modelCube = glm::translate(modelCube, glm::vec3(2.1f, -0.695f, 0.3f));
		modelCube = glm::scale(modelCube, glm::vec3(0.35f, 0.35f, 0.35f));
		outLineShader.Use();
		outLineShader.setMat4("model", modelCube);
		outLineShader.setMat4("view", view);
		outLineShader.setMat4("projection", projection);
		outLineShader.setVec3("inColor", glm::vec3(0.3f, 0.3f, 0.3f));
		cube.Draw(outLineShader);
			//#2
		modelCube = glm::mat4();
		modelCube = glm::translate(modelCube, glm::vec3(3.0f, -0.695f, -0.7f));
		modelCube = glm::scale(modelCube, glm::vec3(0.35f, 0.35f, 0.35f));
		outLineShader.setMat4("model", modelCube);
		cube.Draw(outLineShader);
		glStencilMask(0);
		glEnable(GL_DEPTH_TEST);

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	system("pause");

	return 0;
}

void do_movement() {
	if (keys[GLFW_KEY_W]) camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S]) camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A]) camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D]) camera.ProcessKeyboard(RIGHT, deltaTime);
	if (keys[GLFW_KEY_SPACE]) camera.ProcessKeyboard(UP, deltaTime);
	if (keys[GLFW_KEY_LEFT_SHIFT]) camera.ProcessKeyboard(DOWN, deltaTime);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key >= 1 && key <= 1024) {
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)	glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_P && action == GLFW_PRESS) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (key == GLFW_KEY_O && action == GLFW_PRESS) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	camera.ProcessMouseMovement(xoffset, yoffset, true);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(yoffset);
}
