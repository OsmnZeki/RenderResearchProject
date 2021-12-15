#ifndef MODEL_H
#define	MODEL_H

#include "GLAD/glad.h"
#include <GLFW/glfw3.h>

#include "ASSIMP/Importer.hpp"
#include "ASSIMP/scene.h"
#include "ASSIMP/postprocess.h"

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <vector>
#include "Graphics/Objects/Mesh.h"


class Model {
public:

	glm::vec3 pos;
	glm::vec3 size;

	Model(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f), bool noTex = false);

	void Initialize();
	void LoadModel(std::string path);

	void Render(Shader shader);
	void CleanUp();

protected:
	bool noTex;

	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> textureLoaded;

	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadTextures(aiMaterial* mat, aiTextureType type);

};

#endif 
