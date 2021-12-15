#ifndef LAMP_H
#define LAMP_H

#include "Cube.h"
#include "Graphics/Rendering/Light.h"

class Lamp : public Cube {

public:
	glm::vec3 lightColor;

	//light strenth values
	PointLight pointLight;

	Lamp() {}

	Lamp(glm::vec3 lightColor,
		glm::vec4 ambient,
		glm::vec4 diffuse,
		glm::vec4 specular,
		float k0,
		float k1,
		float k2,
		glm::vec3 pos,
		glm::vec3 size)
		: lightColor(lightColor),
		pointLight({ pos, k0, k1, k2, ambient, diffuse, specular }),
		Cube(pos, size) {}

	void Render(Shader shader) {
		//set light color

		shader.Set3Float("lightColor", lightColor);

		Cube::Render(shader);
	}

};

#endif