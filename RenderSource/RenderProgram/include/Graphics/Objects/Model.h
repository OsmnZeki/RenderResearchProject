#ifndef MODEL_H
#define	MODEL_H

#include "GLAD/glad.h"
#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <vector>
#include "Graphics/Objects/Mesh.h"


class Model {
public:
	std::vector<Mesh> meshes;
	Model();
	void Initialize();
	void Render(Shader shader);
	void CleanUp();
};

#endif 
