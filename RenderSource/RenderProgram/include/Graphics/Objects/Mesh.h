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

enum MeshSetupConfiguration {
	PosSetup = 0,
	PosNormalSetup = 1,
	PosNormalTexCoordSetup = 2
};

class Mesh {
public:
	int verticesSize;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	bool noTex;

	unsigned int VAO;

	std::vector<Texture> textures;

	glm::vec4 diffuse;
	glm::vec4 specular;

	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int>indices, std::vector<Texture> textures = { });
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int>indices, aiColor4D diffuse, aiColor4D specular);
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int>indices, glm::vec4 diffuse, glm::vec4 specular);

	void Render(Shader shader);
	void CleanUp();
	void Setup(MeshSetupConfiguration setupConfig);

private:
	unsigned int VBO, EBO;

	
};

#endif