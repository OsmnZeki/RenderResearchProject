#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include "Shader.h"

struct PointLight {

	glm::vec3 position;

	// attenuation constants
	float k0;
	float k1;
	float k2;
	
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	void Render(Shader shader, int idx);

};


struct DirectionalLight {
	
	glm::vec3 direction;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	void Render(Shader shader);
};


struct SpotLight {

	glm::vec3 position;
	glm::vec3 direction;
	float cutOff;
	float outerCutOff;

	// attenuation constants
	float k0;
	float k1;
	float k2;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	void Render(Shader shader, int idx);
};


#endif 
