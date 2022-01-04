#ifndef _RENDER_PROGRAM_DLL_H_
#define _RENDER_PROGRAM_DLL_H_

#define _RENDER_PROGRAM_DLL_H_ extern "C" __declspec(dllexport)

#include"include/RenderProgram.h"
#include"include/Screen.h"
#include"iostream"


	//screen functions
	_RENDER_PROGRAM_DLL_H_ Screen* CreateScreen();
	_RENDER_PROGRAM_DLL_H_ bool ScreenShouldClose(Screen* screen);
	_RENDER_PROGRAM_DLL_H_ void ScreenUpdate(Screen* screen);
	_RENDER_PROGRAM_DLL_H_ void ScreenNewFrame(Screen* screen);
	_RENDER_PROGRAM_DLL_H_ void ScreenTerminate(Screen* screen);
	_RENDER_PROGRAM_DLL_H_ void ScreenProcessInput(Screen* screen);


#endif