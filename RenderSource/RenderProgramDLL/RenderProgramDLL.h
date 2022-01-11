#ifndef _RENDER_PROGRAM_DLL_H_
#define _RENDER_PROGRAM_DLL_H_

#define _RENDER_PROGRAM_DLL_H_ extern "C" __declspec(dllexport)

#include"RenderProgram.h"
#include"Screen.h"
#include "Graphics/Rendering/Shader.h"
#include "Graphics/Objects/Model.h"
#include "IO/KeyboardInput.h"
#include "IO/MouseInput.h"

#include"iostream"

	//screen functions
	_RENDER_PROGRAM_DLL_H_ Screen* CreateScreen(int width, int height);
	_RENDER_PROGRAM_DLL_H_ bool ScreenShouldClose(Screen* screen);
	_RENDER_PROGRAM_DLL_H_ void ScreenUpdate(Screen* screen);
	_RENDER_PROGRAM_DLL_H_ void ScreenNewFrame(Screen* screen);
	_RENDER_PROGRAM_DLL_H_ void ScreenTerminate(Screen* screen);
	_RENDER_PROGRAM_DLL_H_ void ScreenProcessInput(Screen* screen);

	//shader functions
	_RENDER_PROGRAM_DLL_H_ Shader* NewShader(const char* vertexShaderPath, const char* fragShaderPath);
	_RENDER_PROGRAM_DLL_H_ void ShaderSetInt(Shader* shader, const char* name, int value);
	_RENDER_PROGRAM_DLL_H_ void ShaderSetFloat(Shader* shader, const char* name, float value);
	_RENDER_PROGRAM_DLL_H_ void ShaderSet3Float(Shader* shader, const char* name, float value, float value1, float value2);
	_RENDER_PROGRAM_DLL_H_ void ShaderSet4Float(Shader* shader, const char* name, float value, float value1, float value2, float value3);
	_RENDER_PROGRAM_DLL_H_ void ShaderSetBool(Shader* shader, const char* name, bool value);
	_RENDER_PROGRAM_DLL_H_ void ShaderSetMat4(Shader* shader, const char* name, glm::mat4* val);
	_RENDER_PROGRAM_DLL_H_ void ShaderActivate(Shader* shader);

	//Texture functions
	_RENDER_PROGRAM_DLL_H_ Texture* NewTexture(const char* directory, const char* name, int type);
	_RENDER_PROGRAM_DLL_H_ void TextureLoad(Texture* texture, bool flip);

	//Mesh functions
	_RENDER_PROGRAM_DLL_H_ Mesh* CreateMesh();
	_RENDER_PROGRAM_DLL_H_ void MeshSetVerticesPos(Mesh* mesh, float* pos, int sizeOfVertices);
	_RENDER_PROGRAM_DLL_H_ void MeshSetIndices(Mesh* mesh, int* indices);
	_RENDER_PROGRAM_DLL_H_ void MeshSetVerticesNormal(Mesh* mesh, float* normal);
	_RENDER_PROGRAM_DLL_H_ void MeshSetVerticesTexCoord(Mesh* mesh, float* texCoord);
	_RENDER_PROGRAM_DLL_H_ void AddTextureToMesh(Mesh* mesh, Texture* texture);
	_RENDER_PROGRAM_DLL_H_ void MeshCleanUp(Mesh* mesh);
	_RENDER_PROGRAM_DLL_H_ void MeshSetup(Mesh* mesh,int setupConfig);
	_RENDER_PROGRAM_DLL_H_ void MeshSetDiffuse(Mesh* mesh, float* diffuse);
	_RENDER_PROGRAM_DLL_H_ void MeshSetSpecular(Mesh* mesh, float* specular);
	

	//model functions
	_RENDER_PROGRAM_DLL_H_ Model* NewModel();
	_RENDER_PROGRAM_DLL_H_ void LoadModel(Model* model, const char* modelPath);
	_RENDER_PROGRAM_DLL_H_ void ModelRender(Model* model, Shader* shader);
	_RENDER_PROGRAM_DLL_H_ void ModelCleanUp(Model* model);
	_RENDER_PROGRAM_DLL_H_ void AddMeshToModel(Model* model, Mesh* mesh);
	_RENDER_PROGRAM_DLL_H_ void SetPosAndSize(Model* model, float* pos, float* size); //test
	_RENDER_PROGRAM_DLL_H_ Mesh* GetMesh(Model* model,int meshIdx);

	//input functions
	_RENDER_PROGRAM_DLL_H_ bool GetKeyDown(int keyCode);
	_RENDER_PROGRAM_DLL_H_ bool GetKeyUp(int keyCode);
	_RENDER_PROGRAM_DLL_H_ bool GetKey(int keyCode);
	_RENDER_PROGRAM_DLL_H_ bool GetMouseKeyDown(int keyCode);
	_RENDER_PROGRAM_DLL_H_ bool GetMouseKeyUp(int keyCode);
	_RENDER_PROGRAM_DLL_H_ bool GetMouseKey(int keyCode);
	_RENDER_PROGRAM_DLL_H_ double GetMouseX();
	_RENDER_PROGRAM_DLL_H_ double GetMouseY();
	_RENDER_PROGRAM_DLL_H_ double GetDx();
	_RENDER_PROGRAM_DLL_H_ double GetDy();
	_RENDER_PROGRAM_DLL_H_ double GetScrollDx();
	_RENDER_PROGRAM_DLL_H_ double GetScrollDy();

	//GLMatrix functions
	_RENDER_PROGRAM_DLL_H_ glm::mat4* ReturnMat4(float value);
	
	//GLMath functions
	_RENDER_PROGRAM_DLL_H_ glm::mat4* LookAt(float* cameraPos, float* cameraFront, float* cameraUp);
	_RENDER_PROGRAM_DLL_H_ glm::mat4* Perspective(float fovy, float aspect, float near, float far);
	_RENDER_PROGRAM_DLL_H_ void Rotate(glm::mat4* modelMatrix, float degree, float* axisOfRotation, float* newDirection);

#endif