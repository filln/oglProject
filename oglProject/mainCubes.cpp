#define GLEW_STATIC
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
//#include "Model.h"
#include "shader.h"
#include "Camera.h"
#include "Textures.h"
#include "Figures.h"
#include "Materials.h"
#include "Lamps.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void do_movement();

const GLchar
	*vertexPath = "shaders/cubeTexLight.vs",
	*fragmentPath = "shaders/cubeTexLight.fs",
	*vertexLightPath = "shaders/lightcube.vs",
	*fragmentLightPath = "shaders/lightcube.fs",
	*texture1Path = "tex/container.jpg",
	*texture2Path = "tex/awesomeface.png",
	*texture3Path = "tex/container2.png",
	*texture3SpecPath = "tex/container2_specular.png";
//	*modelPath = "tex/nanosuit/nanosuit.obj";

Camera camera;
Textures texture;
Figures figure;
Materials material;
const GLuint ourLampsCount = 6;
Lamps ourLamps[ourLampsCount];

//Model nanosuit(modelPath);

bool keys[1024];

float interpol = 0.2;
//const GLuint WIDTH = 800, HEIGHT = 600;
//const GLuint WIDTH = 1920, HEIGHT = 1080;
const GLuint WIDTH = 1024, HEIGHT = 768;

GLfloat
	deltaTime = 0.0f, lastFrame = 0.0f,
	lastX = (GLfloat)WIDTH / 2, lastY = (GLfloat)HEIGHT / 2;

int main() {
	//glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	//glm::mat4 trans;
	//trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
	//vec = trans * vec;
	//std::cout << vec.x << vec.y << vec.z << std::endl;

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
	std::cout<<glGetString(GL_VERSION)<<std::endl;
	//GLint nrAttributes;
	//glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	//std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
	glEnable(GL_DEPTH_TEST);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	for (int i = 0; i < ourLampsCount; ++i) {
		ourLamps[i].SetDistance(65);
	}

	camera.FPScam = true;
	Shader
		ourShader(vertexPath, fragmentPath),
		lightShader(vertexLightPath, fragmentLightPath);
	
	const GLuint
		sizeVer = 192, sizeInd = 36,
		sizeVerLight = 144;
	GLfloat vertices[sizeVer], verticesLight[sizeVerLight];
	GLuint indices[sizeInd];
	figure.Cube192(vertices, sizeVer, indices, sizeInd);
	figure.Cube144(verticesLight, sizeVerLight, indices, sizeInd);
	GLsizeiptr 
		sizeofVer = sizeof(vertices),
		sizeofVerLight = sizeof(verticesLight),
		sizeofInd = sizeof(indices);

	const GLuint cubeCount = 10;
	glm::vec3 cubePositions[cubeCount] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	ourLamps[0].position = glm::vec3(0.7f, 0.2f, 2.0f);
	ourLamps[1].position = glm::vec3(2.3f, -3.3f, -4.0f);
	ourLamps[2].position = glm::vec3(-4.0f, 2.0f, -12.0f);
	ourLamps[3].position = glm::vec3(0.0f, 0.0f, -3.0f);
	ourLamps[0].color = glm::vec3(1.0f, 0.6f, 0.0f);
	ourLamps[1].color = glm::vec3(1.0f, 0.0f, 0.0f);
	ourLamps[2].color = glm::vec3(1.0f, 1.0, 0.0);
	ourLamps[3].color = glm::vec3(0.2f, 0.2f, 1.0f);
	for (int i = 0; i < ourLampsCount; ++i)
		ourLamps[i].SetColors();

	GLuint 
		VAO, VBO, EBO,
		lightVAO, lightVBO, lightEBO;
	figure.BindVertexCube192(VAO, VBO, EBO, vertices, sizeofVer, indices, sizeofInd);
	figure.BindVertexLightCube144(lightVAO, lightVBO, lightEBO, verticesLight, sizeofVerLight, indices, sizeofInd);

	GLuint
		//texture1 = texture.CreateTexture2D(texture1Path),
		//texture2 = texture.CreateTexture2D(texture2Path),
		texture3 = texture.CreateTexture2D(texture3Path),
		texture3Spec = texture.CreateTexture2D(texture3SpecPath);
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture1);
	//glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, texture2);
	//glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture2"), 1);
	//glUniform1f(glGetUniformLocation(ourShader.Program, "interpol"), interpol);
	
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		do_movement();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model, view, projection;
		view = camera.GetViewMatrix();
		projection = glm::perspective(glm::radians(camera.Zoom), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

		lightShader.Use();
		//light.color = glm::vec3(sin(currTime)*2.0f, sin(currTime)*0.7f, sin(currTime)*1.3f);
		//light.ambient = light.color * glm::vec3(0.1f);
		//light.diffuse = light.color * glm::vec3(0.5f);
		//cubePositions[0].x = sin(glfwGetTime())*5.0f;
//		light.Rotate(cubePositions[4]);
		glBindVertexArray(lightVAO);
		for(GLuint i = 0; i < ourLampsCount; ++i){
			model = glm::mat4();
			model = glm::translate(model, ourLamps[i].position);
			model = glm::scale(model, glm::vec3(0.2f));
			lightShader.setMat4("model", model);
			lightShader.setMat4("view", view);
			lightShader.setMat4("projection", projection);
			lightShader.setVec3("lightColor", ourLamps[i].color);

			glDrawElements(GL_TRIANGLES, sizeInd, GL_UNSIGNED_INT, 0);
		}
		glBindVertexArray(0);

		ourShader.Use();
		glBindVertexArray(VAO);
		for (GLuint i = 0; i < cubeCount; ++i) {
			model = glm::mat4();
			model = glm::translate(model, cubePositions[i]);
//			GLfloat angle = (GLfloat)glfwGetTime() * 20.0f;
//			GLfloat angle = (GLfloat)glfwGetTime() * 20.0f * (i+1);
//			GLfloat angle = -55.0f;
			GLfloat angle = 20.0f * i;
			if(i%3 == 0) angle = (GLfloat)glfwGetTime() * 20.0f;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			ourShader.setMat4("model", model);
			ourShader.setVec3("viewPos", camera.Position);
			glDrawElements(GL_TRIANGLES, sizeInd, GL_UNSIGNED_INT, 0);
		}
		glBindVertexArray(0);
		ourShader.setMat4("view", view);
		ourShader.setMat4("projection", projection);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture3);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture3Spec);

		ourShader.setInt("material.diffuseTex", 0);
		ourShader.setInt("material.specularTex", 1);
		ourShader.setFloat("material.shininessTex", 128);

		ourShader.setVec3("material.ambient", material.ambient);
		ourShader.setVec3("material.diffuse", material.diffuse);
		ourShader.setVec3("material.specular", material.specular);
		ourShader.setFloat("material.shininess", material.shininess);

		ourShader.setVec3("pointLights[0].position", ourLamps[0].position);
		ourShader.setVec3("pointLights[0].ambient", ourLamps[0].ambient);
		ourShader.setVec3("pointLights[0].diffuse", ourLamps[0].diffuse);
		ourShader.setVec3("pointLights[0].specular", ourLamps[0].specular);
		ourShader.setFloat("pointLights[0].constant", ourLamps[0].constant);
		ourShader.setFloat("pointLights[0].linear", ourLamps[0].linear);
		ourShader.setFloat("pointLights[0].quadratic", ourLamps[0].quadratic);

		ourShader.setVec3("pointLights[1].position", ourLamps[1].position);
		ourShader.setVec3("pointLights[1].ambient", ourLamps[1].ambient);
		ourShader.setVec3("pointLights[1].diffuse", ourLamps[1].diffuse);
		ourShader.setVec3("pointLights[1].specular", ourLamps[1].specular);
		ourShader.setFloat("pointLights[1].constant", ourLamps[1].constant);
		ourShader.setFloat("pointLights[1].linear", ourLamps[1].linear);
		ourShader.setFloat("pointLights[1].quadratic", ourLamps[1].quadratic);

		ourShader.setVec3("pointLights[2].position", ourLamps[2].position);
		ourShader.setVec3("pointLights[2].ambient", ourLamps[2].ambient);
		ourShader.setVec3("pointLights[2].diffuse", ourLamps[2].diffuse);
		ourShader.setVec3("pointLights[2].specular", ourLamps[2].specular);
		ourShader.setFloat("pointLights[2].constant", ourLamps[2].constant);
		ourShader.setFloat("pointLights[2].linear", ourLamps[2].linear);
		ourShader.setFloat("pointLights[2].quadratic", ourLamps[2].quadratic);

		ourShader.setVec3("pointLights[3].position", ourLamps[3].position);
		ourShader.setVec3("pointLights[3].ambient", ourLamps[3].ambient);
		ourShader.setVec3("pointLights[3].diffuse", ourLamps[3].diffuse);
		ourShader.setVec3("pointLights[3].specular", ourLamps[3].specular);
		ourShader.setFloat("pointLights[3].constant", ourLamps[3].constant);
		ourShader.setFloat("pointLights[3].linear", ourLamps[3].linear);
		ourShader.setFloat("pointLights[3].quadratic", ourLamps[3].quadratic);

		ourShader.setVec3("dirLight.direction", ourLamps[4].direction);
		ourShader.setVec3("dirLight.ambient", ourLamps[4].ambient);
		ourShader.setVec3("dirLight.diffuse", ourLamps[4].diffuse);
		ourShader.setVec3("dirLight.specular", ourLamps[4].specular);

		ourShader.setVec3("spotLight.direction", camera.Front);
		ourShader.setVec3("spotLight.position", camera.Position);
		ourShader.setVec3("spotLight.ambient", ourLamps[5].ambient);
		ourShader.setVec3("spotLight.diffuse", ourLamps[5].diffuse);
		ourShader.setVec3("spotLight.specular", ourLamps[5].specular);
		ourShader.setFloat("spotLight.constant", ourLamps[5].constant);
		ourShader.setFloat("spotLight.linear", ourLamps[5].linear);
		ourShader.setFloat("spotLight.quadratic", ourLamps[5].quadratic);
		ourShader.setFloat("spotLight.cutOff", ourLamps[5].cutOff);
		ourShader.setFloat("spotLight.outerCutOff", ourLamps[5].outerCutOff);

//		nanosuit.Draw(ourShader);

		glfwSwapBuffers(window);
	}

	figure.DeleteVertexCube(VAO, VBO, EBO);
	figure.DeleteVertexCube(lightVAO, lightVBO, lightEBO);

	glfwTerminate();

	system("pause");

	return 0;
}

void do_movement(){
	if (keys[GLFW_KEY_W]) camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S]) camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A]) camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D]) camera.ProcessKeyboard(RIGHT, deltaTime);
	if (keys[GLFW_KEY_SPACE]) camera.ProcessKeyboard(UP, deltaTime);
	if (keys[GLFW_KEY_LEFT_SHIFT]) camera.ProcessKeyboard(DOWN, deltaTime);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
//	std::cout << key << std::endl;
	if (key >= 1 && key <= 1024) {
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)	glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_P && action == GLFW_PRESS) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (key == GLFW_KEY_O && action == GLFW_PRESS) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS) if(interpol < 1.0f) interpol += 0.1f;
	//if (key == GLFW_KEY_MINUS && action == GLFW_PRESS) {
	//	if (interpol > 0.11f) interpol -= 0.1f;
	//	else interpol = 0.0f;
	//}
	if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS) {
		material.MakeMaterial(++material.name);
	}
	if (key == GLFW_KEY_MINUS && action == GLFW_PRESS) {
		material.MakeMaterial(--material.name);
	}
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
