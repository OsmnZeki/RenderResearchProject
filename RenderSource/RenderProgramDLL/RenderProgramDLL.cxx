#include "RenderProgramDLL.h"

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

