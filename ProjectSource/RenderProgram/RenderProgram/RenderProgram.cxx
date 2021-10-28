#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <iostream>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>
#include"RenderProgram.h"

#include "glad.h"
#include "glfw3.h"

//#include <experimental/filesystem> current path i bulmak istiyosan aç
 


void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);
std::string LoadShaderSrc(const char* filename);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
// TODO: Þimdilik herkes kendi pathini verecek. Daha sonrasýnda C# için ayarlama yapýlacak.
//const char* VertexShaderPath = "D:/ResearchProjectSource/Render/RenderSource/RenderProgram/RenderProgram/Assets/vertex_core.glsl";
//const char* FragmentShaderPath = "D:/ResearchProjectSource/Render/RenderSource/RenderProgram/RenderProgram/Assets/fragment_core.glsl";
const char* VertexShaderPath = "D:/ResearchProject/Source/Render/RenderSource/RenderProgram/RenderProgram/Assets/vertex_core.glsl";
const char* FragmentShaderPath = "D:/ResearchProject/Source/Render/RenderSource/RenderProgram/RenderProgram/Assets/fragment_core.glsl";

void CustomRender::Render() {

    int success;
    char infoLog[512];
    


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

    /*
    shaders
    */

    // compile vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertexShaderSrc = LoadShaderSrc(VertexShaderPath);
    const  GLchar* VertShader = vertexShaderSrc.c_str();
    glShaderSource(vertexShader, 1, &VertShader, NULL);
    glCompileShader(vertexShader);

    // catch error
    glGetShaderiv(vertexShader ,GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Error with vertex shader comp.:" << std::endl << infoLog << std::endl;
    }

    // compile fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentShaderSrc = LoadShaderSrc(FragmentShaderPath);
    const  GLchar* FragShader = fragmentShaderSrc.c_str();
    glShaderSource(fragmentShader, 1, &FragShader, NULL);
    glCompileShader(fragmentShader);

    // catch error
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success); 
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Error with frag shader comp.:" << std::endl << infoLog << std::endl;
    }

    // create program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // catch errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Linking error:" << std::endl << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //VERTEX ARRAY
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    float lastTime;
    GLfloat vert = glGetAttribLocation(shaderProgram, "time");
    //glEnableVertexAttribArray(vert);
   

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        lastTime = glfwGetTime();
        //std::cout << lastTime << std::endl;
        glVertexAttrib1f(vert, lastTime);
        // input
        // -----
        ProcessInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //draw shapes
        glBindVertexArray(VAO);
        glUseProgram(shaderProgram);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
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

std::string LoadShaderSrc(const char* filename) {

    std::ifstream file;
    std::stringstream buf;
    std::string ret = "";

    file.open(filename);
    //std::cout<<std::experimental::filesystem::current_path()<<std::endl;
    
    if (file.is_open()) {

        buf << file.rdbuf();
        ret = buf.str();
    }
    else {
        std::cout << "Could not open " << filename << std::endl;
    }
    file.close();
    return ret;

}

CustomRender::CustomRender()
{
}

CustomRender::~CustomRender()
{
}
