#ifndef SCREEN_H
#define SCREEN_h

#include "GLAD/glad.h"
#include "GLFW/glfw3.h"


class Screen {
public:
	static unsigned int SCR_WIDTH;
	static unsigned int SCR_HEIGHT;

	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	Screen();

	bool Initialize();

	void SetParameters();

	//main loop
	void Update();
	void NewFrame();

	// window closing accessor and modifier
	bool ShouldClose();
	void SetShouldClose(bool shouldClose);

private:
	GLFWwindow* window;

};

#endif 
