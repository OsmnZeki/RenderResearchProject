#include "RenderProgramDLL.h"

#pragma region ScreenFunctions

Screen* CreateScreen(int width, int height)
{
	Screen* screen = new Screen(width, height);

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

void ShaderSetInt(Shader* shader, const char* name, int value)
{
	glUniform1i(glGetUniformLocation(shader->id, name), value);
}

void ShaderSetFloat(Shader* shader, const char* name, float value)
{
	glUniform1f(glGetUniformLocation(shader->id, name), value);
}

void ShaderSet3Float(Shader* shader, const char* name, float value, float value1, float value2)
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

void ShaderSetMat4(Shader* shader, const char* name, glm::mat4* val)
{
	glUniformMatrix4fv(glGetUniformLocation(shader->id, name), 1, GL_FALSE, glm::value_ptr(*val));
}

void ShaderActivate(Shader* shader)
{
	if (shader != NULL) {
		shader->Activate();
	}
}



#pragma endregion

#pragma region TextureFunctions

Texture* NewTexture(const char* directory, const char* name, int type)
{
	Texture* texture = new Texture(directory, name, (aiTextureType)type);
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

	for (int i = 0; i < sizeOfVertices; i++)
	{
		ret[i].pos = glm::vec3(
			pos[i *3 + 0],
			pos[i *3+ 1],
			pos[i *3+ 2]
		);
	}

	mesh->vertices = ret;
}

void MeshSetIndices(Mesh* mesh, int* _indices)
{
	std::vector<unsigned int> ret(mesh->verticesSize);
	for (unsigned int i = 0; i < mesh->verticesSize; i++) {
		ret[i] = _indices[i];
	}
	mesh->indices = ret;
}

void MeshSetVerticesNormal(Mesh* mesh, float* normal)
{
	for (int i = 0; i < mesh->verticesSize; i++)
	{
		mesh->vertices[i].normal = glm::vec3(
			normal[i *3+ 0],
			normal[i *3+ 1],
			normal[i *3+ 2]
		);
	}
}

void MeshSetVerticesTexCoord(Mesh* mesh, float* texCoord)
{
	for (int i = 0; i < mesh->verticesSize; i++)
	{
		mesh->vertices[i].texCoord = glm::vec2(
			texCoord[i *2+ 0],
			texCoord[i *2+ 1]
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
		mesh->Setup((MeshSetupConfiguration)setupConfig);
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

void SetPosAndSize(Model* model, float* pos, float* size)
{
	glm::vec3 vecPos = glm::vec3(pos[0], pos[1], pos[2]);
	glm::vec3 vecSize = glm::vec3(size[0], size[1], size[2]);

	model->pos = vecPos;
	model->size = vecSize;
}

Mesh* GetMesh(Model* model, int meshIdx)
{
	if (model != NULL) {
		return &model->meshes[meshIdx];
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

double GetMouseX()
{
	return MouseInput::GetMouseX();
}

double GetMouseY()
{
	return  MouseInput::GetMouseY();
}

double GetDx()
{
	return MouseInput::GetDx();
}

double GetDy()
{
	return MouseInput::GetDy();
}

double GetScrollDx()
{
	return MouseInput::GetScrollDx();
}

double GetScrollDy()
{
	return MouseInput::GetScrollDy();
}


#pragma endregion

#pragma region GLMatrixFunctions

glm::mat4* ReturnMat4(float value)
{
	glm::mat4* mat4 = new glm::mat4(value);
	return mat4;
}



#pragma endregion

#pragma region GLMathFunction

glm::mat4* LookAt(float* cameraPos, float* cameraFront, float* cameraUp)
{
	glm::vec3 camPos = glm::vec3(cameraPos[0], cameraPos[1], cameraPos[2]);
	glm::mat4* mat4 = new glm::mat4(glm::lookAt(camPos, camPos + glm::vec3(cameraFront[0], cameraFront[1], cameraFront[2]), glm::vec3(cameraUp[0], cameraUp[1], cameraUp[2])));
	return mat4;
}

glm::mat4* Perspective(float fovy, float aspect, float near, float far)
{
	glm::mat4* mat4 = new glm::mat4(glm::perspective(glm::radians(fovy), aspect, near, far));
	return mat4;
}

void Rotate(glm::mat4* modelMatrix, float degree, float* axisOfRotation, float* newDirection) {

	glm::vec3 rotate = glm::vec3(glm::rotate(*modelMatrix, glm::radians(degree), glm::vec3(axisOfRotation[0], axisOfRotation[1], axisOfRotation[2])) * glm::vec4(newDirection[0], newDirection[1], newDirection[2], 1.0f));
	newDirection[0] = rotate.x;
	newDirection[1] = rotate.y;
	newDirection[2] = rotate.z;
}


#pragma endregion







