#ifndef SHADER_H
#define SHADER_H

#include "glad.h"
#include "string"
#include "fstream"
#include "sstream"
#include "iostream"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader {

public:
	unsigned int id;

	Shader(std::string VertexShaderPath, std::string FragmentShaderPath);
	void Activate();

	//utility functions
	std::string LoadShaderSrc(const char* filePath);
	GLuint CompileShader(const char* filePath, GLenum type);

	//uniform functions
	void SetMat4(const std::string& name, glm::mat4 val);



};

#endif