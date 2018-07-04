#include "Lamps.h"

Lamps::Lamps(){
	this->direction = glm::vec3(-0.2f, -1.0f, -0.3f);
	this->position = glm::vec3(1.2f, 1.0f, 1.0f);
	this->firstPosition = this->position;

	this->color = glm::vec3(1.0f, 1.0f, 1.0f);
	this->ambientStrength = 0.05f;
	SetColors();

	this->distance = 50;
	this->constant = 1.0f;
	this->linear = 0.09f;
	this->quadratic = 0.032f;
	this->cutOff = glm::cos(glm::radians(12.5f));
	this->outerCutOff = glm::cos(glm::radians(17.5f));
}

void Lamps::Rotate(glm::vec3 position) {
	glm::vec3 lightRadius = this->firstPosition - position;
	float lightRadiusMod = sqrt(pow(lightRadius.x, 2) + pow(lightRadius.y, 2) + pow(lightRadius.z, 2));
	float currTime = glfwGetTime();
	this->position = glm::vec3(sin(currTime)*lightRadiusMod, cos(currTime)*lightRadiusMod, cos(currTime)*lightRadiusMod);
}

void Lamps::SetDistance(GLuint distance) {
	/*
	http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
	distance	  constant	   linear	  quadratic
		7			1.0			0.7			1.8
		13			1.0			0.35		0.44
		20			1.0			0.22		0.20
		32			1.0			0.14		0.07
		50			1.0			0.09		0.032
		65			1.0			0.07		0.017
		100			1.0			0.045		0.0075
		160			1.0			0.027		0.0028
		200			1.0			0.022		0.0019
		325			1.0			0.014		0.0007
		600			1.0			0.007		0.0002
		3250		1.0			0.0014		0.000007
	*/
	this->distance = distance;
	this->constant = 1.0f;
	switch (distance){
		case 7: {
			this->linear = 0.7f;
			this->quadratic = 1.8f;
			break;
		}
		case 13: {
			this->linear = 0.35f;
			this->quadratic = 0.44f;
			break;
		}
		case 20: {
			this->linear = 0.22f;
			this->quadratic = 0.2f;
			break;
		}
		case 32: {
			this->linear = 0.14f;
			this->quadratic = 0.07f;
			break;
		}
		case 50: {
			this->linear = 0.09f;
			this->quadratic = 0.032f;
			break;
		}
		case 65: {
			this->linear = 0.07f;
			this->quadratic = 0.017f;
			break;
		}
		case 100: {
			this->linear = 0.045f;
			this->quadratic = 0.0075f;
			break;
		}
		case 160: {
			this->linear = 0.027f;
			this->quadratic = 0.0028f;
			break;
		}
		case 200: {
			this->linear = 0.022f;
			this->quadratic = 0.0019f;
			break;
		}
		case 325: {
			this->linear = 0.014f;
			this->quadratic = 0.0007f;
			break;
		}
		case 600: {
			this->linear = 0.007f;
			this->quadratic = 0.0002f;
			break;
		}
		case 3250: {
			this->linear = 0.0014f;
			this->quadratic = 0.000007f;
			break;
		}
		default: {
			break;
		}
	}
}

void Lamps::SetColors() {
	this->ambient = this->color * glm::vec3(1.0f) * this->ambientStrength;
	this->diffuse = this->color * glm::vec3(1.0f);
	this->specular = this->color * glm::vec3(1.0f);
}

Lamps::~Lamps()
{
}
