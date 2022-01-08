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
	_RENDER_PROGRAM_DLL_H_ Screen* CreateScreen();
	_RENDER_PROGRAM_DLL_H_ bool ScreenShouldClose(Screen* screen);
	_RENDER_PROGRAM_DLL_H_ void ScreenUpdate(Screen* screen);
	_RENDER_PROGRAM_DLL_H_ void ScreenNewFrame(Screen* screen);
	_RENDER_PROGRAM_DLL_H_ void ScreenTerminate(Screen* screen);
	_RENDER_PROGRAM_DLL_H_ void ScreenProcessInput(Screen* screen);

	//shader functions
	_RENDER_PROGRAM_DLL_H_ Shader* NewShader(const char* vertexShaderPath, const char* fragShaderPath);

	//model functions
	_RENDER_PROGRAM_DLL_H_ Model* NewModel();
	_RENDER_PROGRAM_DLL_H_ void LoadModel(Model* model, const char* modelPath);
	_RENDER_PROGRAM_DLL_H_ void Render(Model* model, Shader* shader);
	_RENDER_PROGRAM_DLL_H_ void CleanUp(Model* model);

	//input functions
	_RENDER_PROGRAM_DLL_H_ bool GetKeyDown(int keyCode);
	_RENDER_PROGRAM_DLL_H_ bool GetKeyUp(int keyCode);
	_RENDER_PROGRAM_DLL_H_ bool GetKey(int keyCode);
	_RENDER_PROGRAM_DLL_H_ bool GetMouseKeyDown(int keyCode);
	_RENDER_PROGRAM_DLL_H_ bool GetMouseKeyUp(int keyCode);
	_RENDER_PROGRAM_DLL_H_ bool GetMouseKey(int keyCode);

#endif