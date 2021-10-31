#include "Shader.h"


Shader::Shader( std::string VertexShaderPath,  std::string FragmentShaderPath) {
	int success;
	char infoLog[512];

	const char* vertexPath = VertexShaderPath.c_str();
	const char* fragmentPath = FragmentShaderPath.c_str();

	GLuint vertexShader = CompileShader(vertexPath, GL_VERTEX_SHADER);
	GLuint fragmentShader = CompileShader(fragmentPath, GL_FRAGMENT_SHADER);

	id = glCreateProgram();

	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << "Linking error:" << std::endl << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


//aktif shaderi belirlemek için kullanýlýyor
void Shader::Activate() {
	glUseProgram(id);
}


//utility functions
std::string Shader::LoadShaderSrc(const char* filename) {

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

GLuint Shader::CompileShader(const char* filePath, GLenum type) {
	int success;
	char infoLog[512];

	GLuint ret = glCreateShader(type);
	std::string shaderPath = LoadShaderSrc(filePath);
	const GLchar* shader = shaderPath.c_str();
	glShaderSource(ret, 1, &shader, NULL);
	glCompileShader(ret);

	// catch error
	glGetShaderiv(ret, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(ret, 512, NULL, infoLog);
		std::cout << "Error with vertex shader comp.:" << std::endl << infoLog << std::endl;
	}

	return ret;
}

//uniform functions (shader içerisine deðer atamak için)
//fonksiyonlar aktif shader için çalýþacak
//shader içerisindeki mat4 deðiþkenine deðer atar
void Shader::SetMat4(const std::string& name, glm::mat4 val) {
	Activate();
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));

}