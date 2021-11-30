#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <iostream>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>
#include"RenderProgram.h"

#include "STB/stb_image.h"

#include "glad.h"
#include "glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Shader.h"
#include "FilePaths.h"
#include "Texture.h"

#include "KeyboardInput.h"
#include "MouseInput.h"

#include "Camera.h"
#include "Screen.h"
#include "Cube.h"
//#include <experimental/filesystem> current path i bulmak istiyosan aç

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(double dt);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

Screen screen;

float mixVal = 0.5f;

glm::mat4 transform = glm::mat4(1.0f);

Camera cameras[2] = {
	Camera(glm::vec3(0.0f, 0.0f,3.0f)),
	Camera(glm::vec3(0, 0, 15.0f))
};

int activeCamera = 0;

//Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void CustomRender::Render() {



	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	if (!screen.Initialize())
	{
		return;
	}

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	screen.SetParameters();

	//shaders compile
	Shader shader(FilePath::ShadersPath + "object.vs", FilePath::ShadersPath + "object.fs");

	Cube cube(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.75f));
	cube.Initialize();
	

	// render loop
	while (!screen.ShouldClose())
	{
		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		// input
		ProcessInput(deltaTime);

		// render
		// ------
		screen.Update();

		

		//create transformations for screen
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		view = cameras[activeCamera].GetViewMatrix();
		projection = glm::perspective(glm::radians(cameras[activeCamera].GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		shader.SetMat4("model", model);
		shader.SetMat4("view", view);
		shader.SetMat4("projection", projection);
		shader.SetFloat("mixVal", mixVal);

		cube.Render(shader);
		screen.NewFrame();
	}
	cube.CleanUp();
	glfwTerminate();
}

void ProcessInput(double dt)
{
	if (KeyboardInput::Key(GLFW_KEY_ESCAPE)) {
		screen.SetShouldClose(true);
	}


	if (KeyboardInput::Key(GLFW_KEY_UP)) {
		mixVal += 0.05f;
		if (mixVal > 1)
			mixVal = 1;
	}
	if (KeyboardInput::Key(GLFW_KEY_DOWN)) {
		mixVal -= 0.05f;
		if (mixVal < 0)
			mixVal = 0;
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
	}


}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
}


CustomRender::CustomRender()
{
}

CustomRender::~CustomRender()
{
}
