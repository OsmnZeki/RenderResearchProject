#ifndef MESH_H
#define MESH_H

#include "GLAD/glad.h"
#include <GLFW/glfw3.h>

#include <vector>
#include <GLM/glm.hpp>

#include "Graphics/Rendering/Shader.h"
#include "Graphics/Rendering/Texture.h"

struct Vertex {
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 texCoord;

	static std::vector<struct Vertex> SetVertices(float* vertices, int numOfVertices);
};
typedef struct Vertex Vertex;

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int VAO;

	std::vector<Texture> textures;

	aiColor4D diffuse;
	aiColor4D specular;

	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int>indices, std::vector<Texture> textures = { });
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int>indices, aiColor4D diffuse, aiColor4D specular);

	void Render(Shader shader);
	void CleanUp();

private:
	unsigned int VBO, EBO;

	bool noTex;

	void Setup();
};

#endif