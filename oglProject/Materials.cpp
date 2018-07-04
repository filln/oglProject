#include "Materials.h"

Materials::Materials(){
	MakeMaterial(minName);
}
Materials::Materials(GLuint name) {
	MakeMaterial(name);
}
void Materials::MakeMaterial(GLuint name) {
	//http://devernay.free.fr/cours/opengl/materials.html
	this->name = checkLimitsEnum(name);
	switch (this->name) {
		case emerald: {
			this->ambient = glm::vec3(0.0215f, 0.1745f, 0.0215f);
			this->diffuse = glm::vec3(0.07568f, 0.61424f, 0.07568f);
			this->specular = glm::vec3(0.633f, 0.727811f, 0.633f);
			this->shininess = 0.6f;
			break;
		}
		case jade: {
			this->ambient = glm::vec3(0.135f, 0.2225f, 0.1575f);
			this->diffuse = glm::vec3(0.54f, 0.89f, 0.63f);
			this->specular = glm::vec3(0.316228f, 0.316228f, 0.316228f);
			this->shininess = 0.1f;
			break;
		}
		case obsidian: {
			this->ambient = glm::vec3(0.05375f, 0.05f, 0.06625f);
			this->diffuse = glm::vec3(0.18275f, 0.17f, 0.22525f);
			this->specular = glm::vec3(0.332741f, 0.328634f, 0.346435f);
			this->shininess = 0.3f;
			break;
		}
		case pearl: {
			this->ambient = glm::vec3(0.25f, 0.20725f, 0.20725f);
			this->diffuse = glm::vec3(1.0f, 0.829f, 0.829f);
			this->specular = glm::vec3(0.296648f, 0.296648f, 0.296648f);
			this->shininess = 0.088f;
			break;
		}
		case ruby: {
			this->ambient = glm::vec3(0.1745f, 0.01175f, 0.01175f);
			this->diffuse = glm::vec3(0.61424f, 0.04136f, 0.04136f);
			this->specular = glm::vec3(0.727811f, 0.626959f, 0.626959f);
			this->shininess = 0.6f;
			break;
		}
		case turquoise: {
			this->ambient = glm::vec3(0.1f, 0.18725f, 0.1745f);
			this->diffuse = glm::vec3(0.396f, 0.74151f, 0.69102f);
			this->specular = glm::vec3(0.297254f, 0.30829f, 0.306678f);
			this->shininess = 0.1f;
			break;
		}
		case brass: {
			this->ambient = glm::vec3(0.329412f, 0.223529f, 0.027451f);
			this->diffuse = glm::vec3(0.780392f, 0.568627f, 0.113725f);
			this->specular = glm::vec3(0.992157f, 0.941176f, 0.807843f);
			this->shininess = 0.21794872f;
			break;
		}
		case bronze: {
			this->ambient = glm::vec3(0.2125f, 0.1275f, 0.054f);
			this->diffuse = glm::vec3(0.714f, 0.4284f, 0.18144f);
			this->specular = glm::vec3(0.393548f, 0.271906f, 0.166721f);
			this->shininess = 0.2f;
			break;
		}
		case chrome: {
			this->ambient = glm::vec3(0.25f, 0.25f, 0.25f);
			this->diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
			this->specular = glm::vec3(0.774597f, 0.774597f, 0.774597f);
			this->shininess = 0.6f;
			break;
		}
		case copper: {
			this->ambient = glm::vec3(0.19125f, 0.0735f, 0.0225f);
			this->diffuse = glm::vec3(0.7038f, 0.27048f, 0.0828f);
			this->specular = glm::vec3(0.256777f, 0.137622f, 0.086014f);
			this->shininess = 0.1f;
			break;
		}
		case gold: {
			this->ambient = glm::vec3(0.24725f, 0.1995f, 0.0745f);
			this->diffuse = glm::vec3(0.75164f, 0.60648f, 0.22648f);
			this->specular = glm::vec3(0.628281f, 0.555802f, 0.366065f);
			this->shininess = 0.4f;
			break;
		}
		case silver: {
			this->ambient = glm::vec3(0.19225f, 0.19225f, 0.19225f);
			this->diffuse = glm::vec3(0.50754f, 0.50754f, 0.50754f);
			this->specular = glm::vec3(0.508273f, 0.508273f, 0.508273f);
			this->shininess = 0.4f;
			break;
		}
		case black_plastic: {
			this->ambient = glm::vec3(0.0f, 0.0f, 0.0f);
			this->diffuse = glm::vec3(0.01f, 0.01f, 0.01f);
			this->specular = glm::vec3(0.50f, 0.50f, 0.50f);
			this->shininess = 0.25f;
			break;
		}
		case cyan_plastic: {
			this->ambient = glm::vec3(0.0f, 0.1f, 0.06f);
			this->diffuse = glm::vec3(0.0f, 0.50980392f, 0.50980392f);
			this->specular = glm::vec3(0.50196078f, 0.50196078f, 0.50196078f);
			this->shininess = 0.25f;
			break;
		}
		case green_plastic: {
			this->ambient = glm::vec3(0.0f, 0.0f, 0.0f);
			this->diffuse = glm::vec3(0.1f, 0.35f, 0.1f);
			this->specular = glm::vec3(0.45f, 0.55f, 0.45f);
			this->shininess = 0.25f;
			break;
		}
		case red_plastic: {
			this->ambient = glm::vec3(0.0f, 0.0f, 0.0f);
			this->diffuse = glm::vec3(0.5f, 0.0f, 0.0f);
			this->specular = glm::vec3(0.7f, 0.6f, 0.6f);
			this->shininess = 0.25f;
			break;
		}
		case white_plastic: {
			this->ambient = glm::vec3(0.0f, 0.0f, 0.0f);
			this->diffuse = glm::vec3(0.55f, 0.55f, 0.55f);
			this->specular = glm::vec3(0.70f, 0.70f, 0.70f);
			this->shininess = 0.25f;
			break;
		}
		case yellow_plastic: {
			this->ambient = glm::vec3(0.0f, 0.0f, 0.0f);
			this->diffuse = glm::vec3(0.5f, 0.5f, 0.0f);
			this->specular = glm::vec3(0.60f, 0.60f, 0.50f);
			this->shininess = 0.25f;
			break;
		}
		case black_rubber: {
			this->ambient = glm::vec3(0.02f, 0.02f, 0.02f);
			this->diffuse = glm::vec3(0.01f, 0.01f, 0.01f);
			this->specular = glm::vec3(0.4f, 0.4f, 0.4f);
			this->shininess = 0.078125f;
			break;
		}
		case cyan_rubber: {
			this->ambient = glm::vec3(0.0f, 0.05f, 0.05f);
			this->diffuse = glm::vec3(0.4f, 0.5f, 0.5f);
			this->specular = glm::vec3(0.04f, 0.7f, 0.7f);
			this->shininess = 0.078125f;
			break;
		}
		case green_rubber: {
			this->ambient = glm::vec3(0.0f, 0.05f, 0.0f);
			this->diffuse = glm::vec3(0.4f, 0.5f, 0.4f);
			this->specular = glm::vec3(0.04f, 0.7f, 0.04f);
			this->shininess = 0.078125f;
			break;
		}
		case red_rubber: {
			this->ambient = glm::vec3(0.05f, 0.0f, 0.0f);
			this->diffuse = glm::vec3(0.5f, 0.4f, 0.4f);
			this->specular = glm::vec3(0.7f, 0.04f, 0.04f);
			this->shininess = 0.078125f;
			break;
		}
		case white_rubber: {
			this->ambient = glm::vec3(0.05f, 0.05f, 0.05f);
			this->diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
			this->specular = glm::vec3(0.7f, 0.7f, 0.7f);
			this->shininess = 0.078125f;
			break;
		}
		case yellow_rubber: {
			this->ambient = glm::vec3(0.05f, 0.05f, 0.0f);
			this->diffuse = glm::vec3(0.5f, 0.5f, 0.4f);
			this->specular = glm::vec3(0.7f, 0.7f, 0.04f);
			this->shininess = 0.078125f;
			break;
		}
		default: {
			//emerald
			this->ambient = glm::vec3(0.0215f, 0.1745f, 0.0215f);
			this->diffuse = glm::vec3(0.07568f, 0.61424f, 0.07568f);
			this->specular = glm::vec3(0.633f, 0.727811f, 0.633f);
			this->shininess = 0.6f;
			break;
		}
	}
	this->shininess *= 128; //2, 4, 8, 16, 32, 64, 128, 256 or 2^1, 2^2, 2^3, 2^4, 2^5, 2^6, 2^7
}
GLuint Materials::checkLimitsEnum(GLuint name) {
	if (name > maxName) name = minName;
	if (name < minName) name = maxName;
	return name;
}

