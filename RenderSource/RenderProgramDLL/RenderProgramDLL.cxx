#include "RenderProgramDLL.h"

#pragma region ScreenFunctions

Screen* CreateScreen()
{
	Screen* screen = new Screen();

	screen->ConfigureGLFW();

	if (!screen->Initialize())
	{
		//return;
	}

	// glad: load all OpenGL function pointers
	if (screen->CheckGladInitialization())
	{
		//return;
	}

	screen->SetParameters();

	return screen;
}

bool ScreenShouldClose(Screen* screen)
{
	return screen->ShouldClose();
}

void ScreenUpdate(Screen* screen)
{
	screen->Update();
}

void ScreenNewFrame(Screen* screen)
{
	screen->NewFrame();
}

void ScreenTerminate(Screen* screen)
{
	screen->Terminate();
}

void ScreenProcessInput(Screen* screen)
{
	screen->ProcessInput();
}

#pragma endregion

#pragma region ShaderFunction

Shader* NewShader(const char* vertexShaderPath, const char* fragShaderPath)
{
	Shader* shader = new Shader(vertexShaderPath, fragShaderPath);
	return shader;
}

void ShaderSetInt(Shader* shader,const char* name, int value)
{
	glUniform1i(glGetUniformLocation(shader->id, name), value);
}

void ShaderSetFloat(Shader* shader,const char* name, float value)
{
	glUniform1f(glGetUniformLocation(shader->id, name), value);
}

void ShaderSet3Float(Shader* shader,const char* name, float value, float value1, float value2)
{
	glUniform3f(glGetUniformLocation(shader->id, name), value, value1, value2);
}

void ShaderSet4Float(Shader* shader, const char* name, float value, float value1, float value2, float value3)
{
	glUniform4f(glGetUniformLocation(shader->id, name), value, value1, value2, value3);
}

void ShaderSetBool(Shader* shader, const char* name, bool value)
{
	glUniform1i(glGetUniformLocation(shader->id, name), (int)value);
}



#pragma endregion

#pragma region TextureFunctions

Texture* NewTexture(const char* directory, const char* name, int type)
{
	Texture* texture = new Texture(directory, name,(aiTextureType)type);
	return texture;
}

void TextureLoad(Texture* texture, bool flip)
{
	texture->Load(flip);
}

#pragma region MeshFunctions
Mesh* CreateMesh()
{
	Mesh* mesh = new Mesh();
	mesh->noTex = true;
	return mesh;
}

void MeshSetVerticesPos(Mesh* mesh, float* pos, int sizeOfVertices)
{
	mesh->verticesSize = sizeOfVertices;
	std::vector<Vertex> ret(sizeOfVertices);

	for (int i = 0; i < sizeOfVertices; i+=3)
	{
		ret[i].pos = glm::vec3(
			pos[i  + 0],
			pos[i  + 1],
			pos[i  + 2]
		);
	}

	mesh->vertices = ret;
}

void MeshSetIndices(Mesh* mesh, int* _indices)
{
	std::vector<unsigned int> indices(mesh->verticesSize);
	for (unsigned int i = 0; i < mesh->verticesSize; i++) {
		mesh->indices[i] = _indices[i];
	}
}

void MeshSetVerticesNormal(Mesh* mesh, float* normal)
{
	for (int i = 0; i < mesh->verticesSize; i += 3)
	{
		mesh->vertices[i].normal= glm::vec3(
			normal[i + 0],
			normal[i + 1],
			normal[i + 2]
		);
	}
}

void MeshSetVerticesTexCoord(Mesh* mesh, float* texCoord)
{
	for (int i = 0; i < mesh->verticesSize; i+=2)
	{
		mesh->vertices[i].texCoord = glm::vec2(
			texCoord[i  + 0],
			texCoord[i  + 1]
		);
	}
}

void AddTextureToMesh(Mesh* mesh, Texture* texture)
{
	if (mesh != NULL && texture != NULL) {
		mesh->noTex = false;
		mesh->textures.push_back(*texture);
	}
}

void MeshCleanUp(Mesh* mesh)
{
	if (mesh != NULL) {
		mesh->CleanUp();
	}
}

void MeshSetup(Mesh* mesh, int setupConfig)
{
	if (mesh != NULL) {
		mesh->Setup((MeshSetupConfiguration) setupConfig);
	}
}

void MeshSetDiffuse(Mesh* mesh, float* diffuse)
{
	if (mesh != NULL) {
		mesh->diffuse = glm::vec4(diffuse[0], diffuse[1], diffuse[2], diffuse[3]);
	}
}

void MeshSetSpecular(Mesh* mesh, float* specular)
{
	if (mesh != NULL) {
		mesh->specular = glm::vec4(specular[0], specular[1], specular[2], specular[3]);
	}
}
#pragma endregion


#pragma region ModelFunctions

Model* NewModel()
{
	Model* model = new Model();
	return model;
}

void LoadModel(Model* model, const char* modelPath)
{
	std::string path = modelPath;
	model->LoadModel(path);
}

void ModelRender(Model* model, Shader* shader)
{
	model->Render(*shader);
}

void ModelCleanUp(Model* model)
{
	model->CleanUp();
}

void AddMeshToModel(Model* model, Mesh* mesh)
{
	if (model != NULL && mesh != NULL) {
		model->meshes.push_back(*mesh);
	}
}

#pragma endregion


#pragma region InputFunctions
bool GetKeyDown(int keyCode)
{
	return KeyboardInput::KeyWentDown(keyCode);
}

bool GetKeyUp(int keyCode)
{
	return KeyboardInput::KeyWentUp(keyCode);
}

bool GetKey(int keyCode)
{
	return KeyboardInput::Key(keyCode);
}

bool GetMouseKeyDown(int keyCode)
{
	return MouseInput::ButtonWentDown(keyCode);
}

bool GetMouseKeyUp(int keyCode)
{
	return MouseInput::ButtonWentUp(keyCode);
}

bool GetMouseKey(int keyCode)
{
	return MouseInput::Button(keyCode);
}

#pragma endregion




