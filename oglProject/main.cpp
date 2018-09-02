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
#include "Scene.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

Camera camera;

bool keys[1024];

float interpol = 0.2;
//const GLuint WIDTH = 800, HEIGHT = 600;
//const GLuint WIDTH = 1920, HEIGHT = 1080;
const GLuint 
	WIDTH = 1024, 
	HEIGHT = 768;

GLfloat
	lastX = (GLfloat)WIDTH / 2, 
	lastY = (GLfloat)HEIGHT / 2;

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

	Scene scene;
//	scene.DrawScene1(camera, window, WIDTH, HEIGHT, keys);
//	scene.DrawScene2(camera, window, WIDTH, HEIGHT, keys);
//	scene.DrawScene3(camera, window, WIDTH, HEIGHT, keys);
//	scene.DrawScene4(camera, window, WIDTH, HEIGHT, keys);
//	scene.DrawScene5(camera, window, WIDTH, HEIGHT, keys);
//	scene.DrawScene6(camera, window, WIDTH, HEIGHT, keys);
//	scene.DrawScene7(camera, window, WIDTH, HEIGHT, keys);
//	scene.DrawScene8(camera, window, WIDTH, HEIGHT, keys);
	scene.DrawScene9(camera, window, WIDTH, HEIGHT, keys);
//	scene.DrawScene10(camera, window, WIDTH, HEIGHT, keys);

	glfwTerminate();

	system("pause");

	return 0;
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
