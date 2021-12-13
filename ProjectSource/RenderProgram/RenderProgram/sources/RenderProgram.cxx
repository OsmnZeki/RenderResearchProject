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
#include "Lamp.h"

#include "Light.h"
//#include <experimental/filesystem> current path i bulmak istiyosan aç

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

bool spotLightOn = true;

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
	Shader lampShader(FilePath::ShadersPath + "object.vs", FilePath::ShadersPath + "lamp.fs");

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.4f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f),
	};

	Cube cubes[10];
	for (int i = 0; i < 10; i++) {
		cubes[i] = Cube(Material::gold,cubePositions[i], glm::vec3(1.0f));
		cubes[i].Initialize();
	}

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f, 0.2f, 2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f, 2.0f, -12.0f),
		glm::vec3(0.0f, 0.0f, -3.0f),
	};

	Lamp lamps[4];
	for (int i = 0; i < 4; i++) {

		lamps[i] = Lamp(glm::vec3(1.0f),
			glm::vec3(0.05f), glm::vec3(0.8f), glm::vec3(1.0f),
			1.0f, 0.07f, 0.032f,
			pointLightPositions[i], glm::vec3(0.25f));

		lamps[i].Initialize();
	}

	DirectionalLight dirLight = {glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.1f), glm::vec3(0.4f), glm::vec3(0.75f)};

	SpotLight spotLight = {
		cameras[activeCamera].cameraPos, cameras[activeCamera].cameraFront,
		glm::cos(glm::radians(5.0f)), glm::cos(glm::radians(10.0f)),
		1.0f, 0.07f, 0.032f,
		glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(1.0f)
	};

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

		shader.Activate();
		shader.Set3Float("viewPos", cameras[activeCamera].cameraPos);

		dirLight.direction =glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(0.5f), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::vec4(dirLight.direction, 1.0f));
		dirLight.Render(shader);

		if (spotLightOn) {
			spotLight.position = cameras[activeCamera].cameraPos;
			spotLight.direction = cameras[activeCamera].cameraFront;
			spotLight.Render(shader, 0);
			shader.SetInt("numbSpotLights", 1);
		}
		else {
			shader.SetInt("numbSpotLights", 0);
		}

		

		for (int i = 0; i < 4; i++) 
		{
			lamps[i].pointLight.Render(shader, i);
		}
		shader.SetInt("numbPointLights", 4);


		//create transformations for screen
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		view = cameras[activeCamera].GetViewMatrix();
		projection = glm::perspective(glm::radians(cameras[activeCamera].GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		shader.SetMat4("view", view);
		shader.SetMat4("projection", projection);
		for (int i = 0; i < 10; i++) {
			cubes[i].Render(shader);
		}

		lampShader.Activate();
		lampShader.SetMat4("view", view);
		lampShader.SetMat4("projection", projection);
		for (int i = 0; i < 4; i++) {
			lamps[i].Render(lampShader);
		}

		screen.NewFrame();
	}

	for (int i = 0; i < 10; i++) {
		cubes[i].CleanUp();
	}

	for (int i = 0; i < 4; i++) {
		lamps[i].CleanUp();
	}

	glfwTerminate();
}

void ProcessInput(double dt)
{
	if (KeyboardInput::Key(GLFW_KEY_ESCAPE)) {
		screen.SetShouldClose(true);
	}


	if (KeyboardInput::KeyWentDown(GLFW_KEY_L)) {
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
	}


}


CustomRender::CustomRender()
{
}

CustomRender::~CustomRender()
{
}
