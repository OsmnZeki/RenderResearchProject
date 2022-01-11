#include "Graphics/Objects/Mesh.h"


std::vector<Vertex> Vertex::SetVertices(float* vertices, int numOfVertices) {
	std::vector<Vertex> ret(numOfVertices);

	int stride = sizeof(Vertex) / sizeof(float);

	for (int i = 0; i < numOfVertices; i++)
	{
		ret[i].pos = glm::vec3(
			vertices[i * stride + 0],
			vertices[i * stride + 1],
			vertices[i * stride + 2]
		);

		ret[i].normal = glm::vec3(
			vertices[i * stride + 3],
			vertices[i * stride + 4],
			vertices[i * stride + 5]

		);

		ret[i].texCoord = glm::vec2(
			vertices[i * stride + 6],
			vertices[i * stride + 7]
		);
	}

	return ret;
}

Mesh::Mesh() {
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
	: vertices(vertices), indices(indices), textures(textures), noTex(false)
{
	Setup(MeshSetupConfiguration::PosNormalTexCoordSetup);
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int>indices, aiColor4D _diffuse, aiColor4D _specular)
	: vertices(vertices), indices(indices), noTex(true)
{
	diffuse.x = _diffuse.r;
	diffuse.y = _diffuse.g;
	diffuse.z = _diffuse.b;
	diffuse.w = _diffuse.a;

	specular.x = _specular.r;
	specular.y = _specular.g;
	specular.z = _specular.b;
	specular.w = _specular.a;
	Setup(MeshSetupConfiguration::PosNormalTexCoordSetup);
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, glm::vec4 _diffuse, glm::vec4 _specular)
{
	diffuse = _diffuse;
	specular = _specular;
	Setup(MeshSetupConfiguration::PosNormalTexCoordSetup);
}

void Mesh::Render(Shader shader)
{
	if (noTex) {
		// materials
		shader.Set4Float("material.diffuse", diffuse);
		shader.Set4Float("material.specular", specular);
		shader.SetInt("noTex", 1);
	}
	else {
		// textures
		unsigned int diffuseIdx = 0;
		unsigned int specularIdx = 0;

		for (unsigned int i = 0; i < textures.size(); i++) {
			// activate texture
			glActiveTexture(GL_TEXTURE0 + i);

			// retrieve texture info
			std::string name;
			switch (textures[i].type)
			{
			case aiTextureType_DIFFUSE:
				name = "diffuse" + std::to_string(diffuseIdx++);
				break;
			case aiTextureType_SPECULAR:
				name = "specular" + std::to_string(specularIdx++);
				break;
			}

			// set the shader value
			shader.SetInt(name, i);
			// bind texture
			textures[i].Bind();
		}
	}

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::CleanUp()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Mesh::Setup(MeshSetupConfiguration setupConfig)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind VAO
	glBindVertexArray(VAO);

	//bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);


	//set vertex attribute pointers
	switch (setupConfig)
	{
	case MeshSetupConfiguration::PosNormalTexCoordSetup:
		//vertex.textcoord
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	case MeshSetupConfiguration::PosNormalSetup:
		//vertex.normal
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	case MeshSetupConfiguration::PosSetup:
		//vertex.position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	default:
		break;
	}

	glBindVertexArray(0);
}
