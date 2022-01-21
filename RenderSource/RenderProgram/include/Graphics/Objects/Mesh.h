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
	int verticesSize;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int>indices);

	
};

#endif