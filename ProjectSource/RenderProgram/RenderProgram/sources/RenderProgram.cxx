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

//#include <experimental/filesystem> current path i bulmak istiyosan a�
 
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }


    //shaders compile
    Shader shader(FilePath::ShadersPath+"/vertex_core.glsl", FilePath::ShadersPath + "/fragment_core.glsl");
    Shader shader2(FilePath::ShadersPath + "/vertex_core.glsl", FilePath::ShadersPath + "/fragment_core2.glsl");

    //VERTEX ARRAY
    float vertices[] = {
        //positions           //colors              //textures
       -0.5f, -0.5f, 0.0f,    1.0f, 1.0f, 0.5f,     0.0f,0.0f, //bottom left
       -0.5f,  0.5f, 0.0f,    0.5f, 1.0f, 0.75f,    0.0f,1.0f, //top left
        0.5f, -0.5f, 0.0f,    0.6f, 1.0f, 0.2f,     1.0f,0.0f, //bottom right
        0.5f,  0.5f, 0.0f,    1.0f, 0.2f, 1.0f,      1.0f,1.0f //top right
    };

    unsigned int indices[] = {
        0,1,2, //first triangle
        3,1,2 // second triangle
    };

    //VAO, VBO
    unsigned int VAO, VBO,EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // bind VAO
    glBindVertexArray(VAO);

    //bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //set attribute pointer
    // 
    //position attribute in vertex shader
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //color attribute in vertex shader
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //texture attribute in vertex shader
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //Textures
    stbi_set_flip_vertically_on_load(true);
    Texture tex1 = Texture(FilePath::ImagePath + "/image2.jpg", 3);
    Texture tex2 = Texture(FilePath::ImagePath + "/image1.png", 4);
    shader.SetInt("texture1",0);
    shader.SetInt("texture2", 1);

    //set up EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
   
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    shader.SetMat4("transform", trans);

    /*glm::mat4 trans2 = glm::mat4(1.0f);
    trans2 = glm::scale(trans2, glm::vec3(1.5f));
    trans2 = glm::rotate(trans2, glm::radians(15.f), glm::vec3(0.0f, 0.0f, 1.0f));
    shader2.SetMat4("transform", trans2);*/

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
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex1.textureID);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tex2.textureID);

        //draw shapes
        glBindVertexArray(VAO);

       // trans = glm::rotate(trans, glm::radians((float)glfwGetTime() / 100.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        //shader.SetMat4("transform", trans); 
        shader.Activate();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


       /* trans2 = glm::rotate(trans2, glm::radians((float)glfwGetTime() / -100.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        shader2.SetMat4("transform", trans2);
        shader2.Activate();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(GLuint)));*/

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VAO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
}

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


CustomRender::CustomRender()
{
}

CustomRender::~CustomRender()
{
}