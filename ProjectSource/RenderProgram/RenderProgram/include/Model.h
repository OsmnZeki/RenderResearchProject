#ifndef MODEL_H
#define	MODEL_H

#include <glad.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <Mesh.h>


class Model {
public:
	std::vector<Mesh> meshes;
	Model();
	void Initialize();
	void Render(Shader shader);
	void CleanUp();
};

#endif 
