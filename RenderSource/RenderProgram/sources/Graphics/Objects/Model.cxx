#include "Graphics/Objects/Model.h"


Model::Model(glm::vec3 pos, glm::vec3 size, bool noTex)
	:pos(pos), size(size), noTex(noTex) {}

void Model::Initialize() {}

void Model::Render(Shader shader)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, pos);
	model = glm::scale(model, size);
	shader.SetMat4("model", model);

	shader.SetFloat("material.shininess", 0.5f);

	for (int i = 0; i < meshes.size(); i++) {
		meshes[i].Render(shader);
	}
}

void Model::CleanUp()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].CleanUp();
	}
}

void Model::LoadModel(std::string path) {
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "Could not load model at " << path << std::endl << import.GetErrorString() << std::endl;
		return;
	}

	directory = path.substr(0, path.find_last_of("/"));
	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene) {
	//process all meshes
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	// vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;

		// position
		vertex.pos = glm::vec3(
			mesh->mVertices[i].x,
			mesh->mVertices[i].y,
			mesh->mVertices[i].z
		);

		// normal vectors
		vertex.normal = glm::vec3(
			mesh->mNormals[i].x,
			mesh->mNormals[i].y,
			mesh->mNormals[i].z
		);

		// textures
		if (mesh->mTextureCoords[0]) {
			vertex.texCoord = glm::vec2(
				mesh->mTextureCoords[0][i].x,
				mesh->mTextureCoords[0][i].y
			);
		}
		else {
			vertex.texCoord = glm::vec2(0.0f);
		}

		vertices.push_back(vertex);
	}

	// process indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	// process materials
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		if (noTex) {
			// diffuse color
			aiColor4D diff(1.0f);
			aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diff);

			// specular color;
			aiColor4D spec(1.0f);
			aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &spec);

			return Mesh(vertices, indices, diff, spec);
		}

		// diffuse maps
		std::vector<Texture> diffuseMaps = LoadTextures(material, aiTextureType_DIFFUSE);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		// specular maps
		std::vector<Texture> specularMaps = LoadTextures(material, aiTextureType_SPECULAR);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::LoadTextures(aiMaterial* mat, aiTextureType type) {
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);

		// prevent duplicate loading
		bool skip = false;
		for (unsigned int j = 0; j < textureLoaded.size(); j++) {
			if (std::strcmp(textureLoaded[j].path.data(), str.C_Str()) == 0) {
				textures.push_back(textureLoaded[j]);
				skip = true;
				break;
			}
		}

		if (!skip) {
			//not loaded yet
			Texture tex(directory, str.C_Str(), type);
			tex.Load(false);
			textures.push_back(tex);
			textureLoaded.push_back(tex);
		}
	}

	return textures;
}
