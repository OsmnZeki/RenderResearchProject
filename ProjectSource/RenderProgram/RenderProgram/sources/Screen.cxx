#include <iostream>
#include "Screen.h"
#include "KeyboardInput.h"
#include "MouseInput.h"

unsigned int Screen::SCR_WIDTH = 800;
unsigned int Screen::SCR_HEIGHT = 600;

void Screen::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
}

Screen::Screen()
	: window(nullptr) {}

bool Screen::Initialize()
{
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Tutorial", NULL, NULL);

	if (!window)
	{
		std::cerr << "Window not created" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	return true;
}

void Screen::SetParameters()
{
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	glfwSetFramebufferSizeCallback(window, Screen::FramebufferSizeCallback);
	glfwSetCursorPosCallback(window, MouseInput::CursorPosCallback);
	glfwSetMouseButtonCallback(window, MouseInput::MouseButtonCallback);
	glfwSetScrollCallback(window, MouseInput::MouseWheelCallback);
	glfwSetKeyCallback(window, KeyboardInput::KeyCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
}

void Screen::Update()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Screen::NewFrame()
{
	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool Screen::ShouldClose()
{
	return glfwWindowShouldClose(window);
}

void Screen::SetShouldClose(bool shouldClose)
{
	glfwSetWindowShouldClose(window, shouldClose);
}
