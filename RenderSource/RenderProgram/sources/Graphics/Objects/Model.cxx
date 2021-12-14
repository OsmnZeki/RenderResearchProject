#include "Graphics/Objects/Model.h"

Model::Model() {}

void Model::Initialize() {}

void Model::Render(Shader shader)
{
	
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
