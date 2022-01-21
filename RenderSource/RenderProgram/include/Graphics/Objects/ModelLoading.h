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
#include "Graphics/Rendering/Material.h"


class ModelLoading {
public:

	std::vector<Mesh> meshes;
	std::vector<Material> materials;

	ModelLoading(bool noTex = false);

	void Initialize();
	void LoadModel(std::string path);

protected:
	bool noTex;

	
	std::string directory;
	std::vector<Texture> textureLoaded;

	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	Material LoadMaterials(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadTextures(aiMaterial* mat, aiTextureType type);

};

#endif 
