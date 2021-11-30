#ifndef MESH_H
#define MESH_H

#include <glad.h>
#include <glfw3.h>

#include <vector>
#include <glm/glm.hpp>

#include "Shader.h"
#include "Texture.h"

struct Vertex {
	glm::vec3 pos;
	glm::vec2 texCoord;

	static std::vector<struct Vertex> genList(float* vertices, int numOfVertices);
};
typedef struct Vertex Vertex;

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int VAO;

	std::vector<Texture> textures;

	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int>indices, std::vector<Texture> textures);

	void Render(Shader shader);
	void CleanUp();

private:
	unsigned int VBO, EBO;

	void Setup();
};

#endif