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

	return screen;
}

_RENDER_PROGRAM_DLL_H_ void ScreenSetParameters(Screen* screen)
{
	screen->SetParameters();
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

void SetClearColor(Screen* screen, float* clearColor)
{
	screen->clearColor = glm::vec4(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
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

#pragma endregion

#pragma region MeshFunctions
Mesh* CreateMesh()
{
	Mesh* mesh = new Mesh();
	return mesh;
}

void MeshSetVerticesPos(Mesh* mesh, float* pos, int sizeOfVertices)
{
	mesh->verticesSize = sizeOfVertices;

	std::vector<Vertex> ret(sizeOfVertices);

	for (int i = 0; i < sizeOfVertices; i++)
	{
		ret[i].pos = glm::vec3(
			pos[i * 3 + 0],
			pos[i * 3 + 1],
			pos[i * 3 + 2]
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
			normal[i * 3 + 0],
			normal[i * 3 + 1],
			normal[i * 3 + 2]
		);
	}
}

void MeshSetVerticesTexCoord(Mesh* mesh, float* texCoord)
{
	for (int i = 0; i < mesh->verticesSize; i++)
	{
		mesh->vertices[i].texCoord = glm::vec2(
			texCoord[i * 2 + 0],
			texCoord[i * 2 + 1]
		);
	}
}

#pragma endregion


#pragma region ModelFunctions

ModelLoading* LoadModel(const char* path)
{
	ModelLoading* modelLoading = new ModelLoading();
	modelLoading->LoadModel(path);
	return modelLoading;
}

int GetTotalMeshCount(ModelLoading* modelLoading)
{
	return modelLoading->meshes.size();
}

int GetTotalMaterialCount(ModelLoading* modelLoading)
{
	return modelLoading->materials.size();
}

Mesh* GetIdxMeshesFromModel(ModelLoading* modelLoading, int idx)
{
	return &modelLoading->meshes[idx];
}

Material* GetIdxMaterialFromModel(ModelLoading* modelLoading, int idx)
{
	return modelLoading->materials[idx];
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

#pragma region MaterialFunctions

Material* NewLitMaterial()
{
	LitMaterial* litMaterial = new LitMaterial();
	return litMaterial;
}

void SetShaderToMaterial(Material* material, Shader* shader)
{
	material->shader = shader;
}

Shader* GetShaderFromMaterial(Material* material)
{
	return material->shader;
}

void SetAmbientToMaterial(LitMaterial* material, float* ambient)
{
	material->ambient = glm::vec4(ambient[0], ambient[1], ambient[2], 1);
}

void SetDiffuseToMaterial(LitMaterial* material, float* diffuse)
{
	material->diffuse = glm::vec4(diffuse[0], diffuse[1], diffuse[2], 1);
}

void SetSpecularToMaterial(LitMaterial* material, float* specular)
{
	material->specular = glm::vec4(specular[0], specular[1], specular[2], 1);
}

void SetShininessToMaterial(LitMaterial* material, float shininess)
{
	material->shininess = shininess;
}

void AddTextureToMaterial(LitMaterial* material, Texture* texture)
{
	material->textures.push_back(*texture);
}

Material* NewUnlitMaterial()
{
	UnlitMaterial* unlitMaterial = new UnlitMaterial();
	return unlitMaterial;
}

void SetColorToMaterial(UnlitMaterial* material, float* color)
{
	material->color = glm::vec4(color[0], color[1], color[2], color[3]);
}

void AddTextureToUnlitMaterial(UnlitMaterial* material, Texture* texture) {
	material->textures.push_back(*texture);
}

#pragma endregion

#pragma region MeshRendererFunctions

MeshRenderer* NewMeshRenderer()
{
	return new MeshRenderer();
}

void SetMeshToMeshRenderer(MeshRenderer* meshRenderer, Mesh* mesh)
{
	meshRenderer->mesh = *mesh;
}

void SetupMeshRenderer(MeshRenderer* meshRenderer)
{
	meshRenderer->Setup();
}

void RenderMeshRenderer(MeshRenderer* meshRenderer, Transform* transform, Material* material)
{
	meshRenderer->Render(*transform,material);
}

void CleanUpMeshRenderer(MeshRenderer* meshRenderer)
{
	meshRenderer->CleanUp();
}


#pragma endregion

#pragma region TransformFunctions

Transform* NewTransform()
{
	return new Transform();
}

void SetTransformPosition(Transform* transform, float* pos)
{
	transform->position = glm::vec3(pos[0], pos[1], pos[2]);
}

void SetTransformSize(Transform* transform, float* size)
{
	transform->size = glm::vec3(size[0], size[1], size[2]);
}

void SetTransformRotation(Transform* transform, float* rotation)
{
	transform->rotation = glm::vec3(rotation[0], rotation[1], rotation[2]);
}

#pragma endregion

#pragma region OpenGLFunctions

void OpenGLEnable(int glEnum)
{
	OpenGLFunctions::GLEnable(glEnum);
}

void OpenGLDisable(int glEnum)
{
	OpenGLFunctions::GLDisable(glEnum);
}

void OpenGLClear(int glEnum)
{
	OpenGLFunctions::GLClear(glEnum);
}

void OpenGLStencilMask(int mask)
{
	OpenGLFunctions::GLStencilMask(mask);
}

void OpenGLStencilFunc(int func, int ref, int mask)
{
	OpenGLFunctions::GLStencilFunc(func, ref, mask);
}

void OpenGLStencilOp(int sfail, int dpfail, int dppass)
{
	OpenGLFunctions::GLStencilOp(sfail, dpfail, dppass);
}


#pragma endregion






