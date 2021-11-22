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
//#include <experimental/filesystem> current path i bulmak istiyosan aç

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
float x, y, z;

float mixVal = 0.5f;

glm::mat4 transform = glm::mat4(1.0f);

void CustomRender::Render() {



	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	// glad: load all OpenGL function pointers
// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
	glfwSetKeyCallback(window, KeyboardInput::KeyCallback);

	glfwSetCursorPosCallback(window, MouseInput::CursorPosCallback);
	glfwSetMouseButtonCallback(window, MouseInput::MouseButtonCallback);
	glfwSetScrollCallback(window, MouseInput::MouseWheelCallback);



	glEnable(GL_DEPTH_TEST);
	//shaders compile
	Shader shader(FilePath::ShadersPath + "/vertex_core.glsl", FilePath::ShadersPath + "/fragment_core.glsl");
	Shader shader2(FilePath::ShadersPath + "/vertex_core.glsl", FilePath::ShadersPath + "/fragment_core2.glsl");

	//VERTEX ARRAY
	float vertices[] = {
		//positions           textcoords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	//VAO, VBO
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// bind VAO
	glBindVertexArray(VAO);

	//bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//set attribute pointer
	// 
	//position attribute in vertex shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//texture attribute in vertex shader
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Textures
	stbi_set_flip_vertically_on_load(true);
	Texture tex1 = Texture(FilePath::ImagePath + "/image2.jpg", 3);
	Texture tex2 = Texture(FilePath::ImagePath + "/image1.png", 4);
	shader.SetInt("texture1", 0);
	shader.SetInt("texture2", 1);

	x = 0.0f;
	y = 0.0f;
	z = 3.0f;

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		ProcessInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex1.textureID);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex2.textureID);

		//draw shapes
		glBindVertexArray(VAO);

		//create transformations for screen
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-55.0f), glm::vec3(0.5f));
		view = glm::translate(view, glm::vec3(-x, -y, -z));
		projection = glm::perspective(glm::radians(90.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		shader.SetMat4("model", model);
		shader.SetMat4("view", view);
		shader.SetMat4("projection", projection);
		shader.SetFloat("mixVal", mixVal);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
}

void ProcessInput(GLFWwindow* window)
{
	if (KeyboardInput::Key(GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, true);
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

	if (KeyboardInput::Key(GLFW_KEY_W)) {

		y += 1 / 5.0f;

	}
	if (KeyboardInput::Key(GLFW_KEY_S)) {

		y -= 1 / 5.0f;
	}
	if (KeyboardInput::Key(GLFW_KEY_A)) {
		x -= 1 / 5.0f;
	}
	if (KeyboardInput::Key(GLFW_KEY_D)) {
		x += 1 / 5.0f;
	}

	if (KeyboardInput::Key(GLFW_KEY_Q)) {
		z += 1 / 5.0f;
	}
	if (KeyboardInput::Key(GLFW_KEY_E)) {
		z -= 1 / 5.0f;
	}

	double dy = MouseInput::GetScrollDy();
	transform = glm::scale(transform, glm::vec3(1 + dy / 10, 1 + dy / 10, 0.0f));

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
