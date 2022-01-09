#ifndef SCREEN_H
#define SCREEN_h

#include "GLAD/glad.h"
#include "GLFW/glfw3.h"

#include "IO/KeyboardInput.h"
#include "IO/MouseInput.h"

class Screen {
public:
	static unsigned int SCR_WIDTH;
	static unsigned int SCR_HEIGHT;

	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	Screen();

	void ConfigureGLFW();
	bool Initialize();
	bool CheckGladInitialization();
	void SetParameters();
	void Terminate();

	//main loop
	void Update();
	void NewFrame();

	// window closing accessor and modifier
	bool ShouldClose();
	void SetShouldClose(bool shouldClose);

	//input
	void ProcessInput();


private:
	GLFWwindow* window;

};

#endif 