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
	Lamps dirLamp(glm::vec3(1.2f, 50.0f, -20.0f), glm::vec3(1.0f, 0.98f, 0.75f));
	Lamps pointLamp(glm::vec3(1.2f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelLamps modelLamps;
	modelLamps.dirLamps = &dirLamp;
	modelLamps.countDirLamps = 1;
	modelLamps.pointLamps = &pointLamp;
	modelLamps.countPointLamps = 1;
	modelLamps.spotLamps = nullptr;
	modelLamps.countSpotLamps = 0;

	Shader
		textureShader(textureVertexPath, textureFragmentPath),
		lampSphereShader(lampSphereVertexPath, lampSphereFragmentPath),
		simpleShader(simpleVertexPath, simpleFragmentPath),
		outLineShader(outLineVertexPath, outLineFragmentPath);
	Model floor(floorPath);
	Model nanosuit(nanosuitPath);
	Model sphere(spherePath);
	Model cube(cubePath);


	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		do_movement();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_STENCIL_TEST);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glStencilMask(0);
		glm::mat4 view, projection;
		view = camera.GetViewMatrix();
		projection = glm::perspective(glm::radians(camera.Zoom), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
		//floor
		floor.DrawTexModel(
			textureShader,
			glm::vec3(0.0f, -1.0f, 0.0f), 90, 0, 0, glm::vec3(1.0f),
			view, projection, camera.Position, 128,
			modelLamps,
			false, nullptr, glm::vec3(0), 0, glm::vec3(0)
		);
		//dirLamps
		sphere.DrawColorModel(
			simpleShader,
			dirLamp.position, 0, 0, 0, glm::vec3(1.0f),
			view, projection,
			dirLamp.color,
			false, nullptr, glm::vec3(0), 0, glm::vec3(0)
		);
		//pointLamps

		//nanosuit


		//cube
		glStencilFunc(GL_ALWAYS, 1, 1);
		glStencilMask(0);
			//#1

			//#2

		//outLine
		glStencilFunc(GL_NOTEQUAL, 0, 1);
		glStencilMask(1);
		glDisable(GL_DEPTH_TEST);
			//#1

			//#2

		glStencilMask(0);
		glEnable(GL_DEPTH_TEST);

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	system("pause");

	return 0;
}

void do_movement() {
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
