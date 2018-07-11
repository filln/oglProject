#include "shader.h"

Shader::Shader(const GLchar * vertexPath, const GLchar * fragmentPath)
{
	std::string vertexCode, fragmentCode;
	std::ifstream vShaderFile, fShaderFile;
	vShaderFile.exceptions(std::ifstream::failbit);
	fShaderFile.exceptions(std::ifstream::failbit);
	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch(std::ifstream::failure e){
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ " <<vertexPath<< std::endl;
	}
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	GLuint vertex, fragment;
	GLint success;
	GLchar infolog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
	}
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
	}

	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragment);
	glLinkProgram(this->Program);
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->Program, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infolog << std::endl;
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void Shader::Use() {
	glUseProgram(this->Program);
}
void Shader::setInt(const GLchar* chName, GLint name) {
	glUniform1i(glGetUniformLocation(this->Program, chName), name);
}

void Shader::setFloat(const GLchar* chName, float name) {
	glUniform1f(glGetUniformLocation(this->Program, chName), name);
}
void Shader::setVec3(const GLchar* chName, glm::vec3 name) {
	glUniform3fv(glGetUniformLocation(this->Program, chName), 1, glm::value_ptr(name));
}
void Shader::setMat4(const GLchar* chName, glm::mat4 name) {
	glUniformMatrix4fv(glGetUniformLocation(this->Program, chName), 1, GL_FALSE, glm::value_ptr(name));
}

void Shader::setDirLamps(Lamps* lamps, const GLuint lampsCount) {
	this->setInt(this->dirLampsCount.c_str(), 2);
	for (GLuint i = 0; i < lampsCount; i++) {
		this->setVec3((this->dirLights + to_string(i) + this->position).c_str(), (lamps + i)->position);
		this->setVec3((this->dirLights + to_string(i) + this->ambient).c_str(), (lamps + i)->ambient);
		this->setVec3((this->dirLights + to_string(i) + this->diffuse).c_str(), (lamps + i)->diffuse);
		this->setVec3((this->dirLights + to_string(i) + this->specular).c_str(), (lamps + i)->specular);
	}
}
void Shader::setPointLamps(Lamps* lamps, const GLuint lampsCount) {
	this->setInt(this->pointLampsCount.c_str(), lampsCount);
	for (GLuint i = 0; i < lampsCount; i++) {
		this->setVec3((this->pointLights + to_string(i) + this->position).c_str(), (lamps + i)->position);
		this->setVec3((this->pointLights + to_string(i) + this->ambient).c_str(), (lamps + i)->ambient);
		this->setVec3((this->pointLights + to_string(i) + this->diffuse).c_str(), (lamps + i)->diffuse);
		this->setVec3((this->pointLights + to_string(i) + this->specular).c_str(), (lamps + i)->specular);
		this->setFloat((this->pointLights + to_string(i) + this->constant).c_str(), (lamps + i)->constant);
		this->setFloat((this->pointLights + to_string(i) + this->linear).c_str(), (lamps + i)->linear);
		this->setFloat((this->pointLights + to_string(i) + this->quadratic).c_str(), (lamps + i)->quadratic);
	}
}
void Shader::setSpotLamps(Lamps* lamps, const GLuint lampsCount) {
	this->setInt(this->spotLampsCount.c_str(), lampsCount);
	for (GLuint i = 0; i < lampsCount; i++) {
		this->setVec3((this->spotLights + to_string(i) + this->direction).c_str(), (lamps + i)->direction);
		this->setVec3((this->spotLights + to_string(i) + this->position).c_str(), (lamps + i)->position);
		this->setVec3((this->spotLights + to_string(i) + this->ambient).c_str(), (lamps + i)->ambient);
		this->setVec3((this->spotLights + to_string(i) + this->diffuse).c_str(), (lamps + i)->diffuse);
		this->setVec3((this->spotLights + to_string(i) + this->specular).c_str(), (lamps + i)->specular);
		this->setFloat((this->spotLights + to_string(i) + this->constant).c_str(), (lamps + i)->constant);
		this->setFloat((this->spotLights + to_string(i) + this->linear).c_str(), (lamps + i)->linear);
		this->setFloat((this->spotLights + to_string(i) + this->quadratic).c_str(), (lamps + i)->quadratic);
		this->setFloat((this->spotLights + to_string(i) + this->cutOff).c_str(), (lamps + i)->cutOff);
		this->setFloat((this->spotLights + to_string(i) + this->outerCutOff).c_str(), (lamps + i)->outerCutOff);
	}
}

Shader::~Shader()
{
}
