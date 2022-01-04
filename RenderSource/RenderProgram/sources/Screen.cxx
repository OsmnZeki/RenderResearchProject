#include <iostream>
#include "Screen.h"
#include "IO/KeyboardInput.h"
#include "IO/MouseInput.h"


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



void Screen::ConfigureGLFW()
{
	if (!glfwInit()) {
		std::cout << "GLFW not initialization" << std::endl;
		return;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}



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

bool Screen::CheckGladInitialization()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return true;
	}
	return false;
}

void Screen::SetParameters()
{
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	glfwSetFramebufferSizeCallback(window, Screen::FramebufferSizeCallback);
	glfwSetCursorPosCallback(window, MouseInput::CursorPosCallback);
	glfwSetMouseButtonCallback(window, MouseInput::MouseButtonCallback);
	glfwSetScrollCallback(window, MouseInput::MouseWheelCallback);
	glfwSetKeyCallback(window, KeyboardInput::KeyCallback);

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
}

void Screen::Terminate()
{
	glfwTerminate();
}

void Screen::Update()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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

void Screen::ProcessInput()
{
		if (KeyboardInput::Key(GLFW_KEY_ESCAPE)) {
			SetShouldClose(true);
		}

		/*if (KeyboardInput::KeyWentDown(GLFW_KEY_L)) {
			spotLightOn = !spotLightOn;
		}

		if (KeyboardInput::KeyWentDown(GLFW_KEY_TAB))
		{
			activeCamera += (activeCamera == 0) ? 1 : -1;
		}

		if (KeyboardInput::Key(GLFW_KEY_SPACE)) {

			cameras[activeCamera].UpdateCameraPos(CameraDirection::UP, dt);
		}
		if (KeyboardInput::Key(GLFW_KEY_LEFT_SHIFT)) {

			cameras[activeCamera].UpdateCameraPos(CameraDirection::DOWN, dt);
		}
		if (KeyboardInput::Key(GLFW_KEY_D)) {

			cameras[activeCamera].UpdateCameraPos(CameraDirection::RIGHT, dt);
		}
		if (KeyboardInput::Key(GLFW_KEY_A)) {

			cameras[activeCamera].UpdateCameraPos(CameraDirection::LEFT, dt);
		}
		if (KeyboardInput::Key(GLFW_KEY_W)) {

			cameras[activeCamera].UpdateCameraPos(CameraDirection::FORWARD, dt);
		}
		if (KeyboardInput::Key(GLFW_KEY_S)) {

			cameras[activeCamera].UpdateCameraPos(CameraDirection::BACKWARD, dt);
		}

		double dx = MouseInput::GetDx();
		double dy = MouseInput::GetDy();
		if (dx != 0 || dy != 0)
		{

			cameras[activeCamera].UpdataCameraDirection(dx, dy);
		}

		double scrollDy = MouseInput::GetScrollDy();
		if (scrollDy != 0)
		{
			cameras[activeCamera].UpdateCameraZoom(scrollDy);
		}*/
}
