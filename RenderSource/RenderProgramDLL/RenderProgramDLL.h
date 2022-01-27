#ifndef _RENDER_PROGRAM_DLL_H_
#define _RENDER_PROGRAM_DLL_H_

#define _RENDER_PROGRAM_DLL_H_ extern "C" __declspec(dllexport)

#include"RenderProgram.h"
#include"Screen.h"
#include "Graphics/Rendering/Shader.h"
#include "Graphics/Objects/ModelLoading.h"
#include "IO/KeyboardInput.h"
#include "IO/MouseInput.h"
#include "MeshRenderer.h"

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

	
	//model functions
	_RENDER_PROGRAM_DLL_H_ ModelLoading* LoadModel(const char* path);
	_RENDER_PROGRAM_DLL_H_ int GetTotalMeshCount(ModelLoading* modelLoading);
	_RENDER_PROGRAM_DLL_H_ int GetTotalMaterialCount(ModelLoading* modelLoading);
	_RENDER_PROGRAM_DLL_H_ Mesh* GetIdxMeshesFromModel(ModelLoading* modelLoading, int idx);
	_RENDER_PROGRAM_DLL_H_ Material* GetIdxMaterialFromModel(ModelLoading* modelLoading, int idx);


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

	//Material functions
	_RENDER_PROGRAM_DLL_H_ Material* NewLitMaterial();
	_RENDER_PROGRAM_DLL_H_ void SetShaderToMaterial(Material* material, Shader* shader);
	_RENDER_PROGRAM_DLL_H_ void SetAmbientToMaterial(LitMaterial* material,float* ambient);
	_RENDER_PROGRAM_DLL_H_ void SetDiffuseToMaterial(LitMaterial* material,float* diffuse);
	_RENDER_PROGRAM_DLL_H_ void SetSpecularToMaterial(LitMaterial* material,float* specular);
	_RENDER_PROGRAM_DLL_H_ void SetShininessToMaterial(LitMaterial* material,float shininess);
	_RENDER_PROGRAM_DLL_H_ void AddTextureToMaterial(LitMaterial* material,Texture* texture);
	_RENDER_PROGRAM_DLL_H_ Material* NewUnlitMaterial();
	_RENDER_PROGRAM_DLL_H_ void SetColorToMaterial(UnlitMaterial* material, float* color);

	//MeshRenderer functions
	_RENDER_PROGRAM_DLL_H_ MeshRenderer* NewMeshRenderer();
	_RENDER_PROGRAM_DLL_H_ void SetMeshToMeshRenderer(MeshRenderer* meshRenderer, Mesh* mesh);
	_RENDER_PROGRAM_DLL_H_ void SetMaterialToMeshRenderer(MeshRenderer* meshRenderer, Material* material);
	_RENDER_PROGRAM_DLL_H_ void SetupMeshRenderer(MeshRenderer* meshRenderer);
	_RENDER_PROGRAM_DLL_H_ void RenderMeshRenderer(MeshRenderer* meshRenderer, Transform* transform);
	_RENDER_PROGRAM_DLL_H_ void CleanUpMeshRenderer(MeshRenderer* meshRenderer);

	//Transform functions
	_RENDER_PROGRAM_DLL_H_ Transform* NewTransform();
	_RENDER_PROGRAM_DLL_H_ void SetTransformPosition(Transform* transform, float* pos);
	_RENDER_PROGRAM_DLL_H_ void SetTransformSize(Transform* transform, float* size);
	_RENDER_PROGRAM_DLL_H_ void SetTransformRotation(Transform* transform, float* rotation);

#endif