
#include "Graphics/Rendering/Material.h"
#include "Graphics/Objects/Mesh.h"

#include <GLM/glm.hpp>
#include "GLAD/glad.h"
#include <GLFW/glfw3.h>

struct Transform {
	glm::vec3 position;
	glm::vec3 size;
	glm::vec3 rotation;
};



class MeshRenderer {

public: 
	Material* material;
	Mesh mesh;
	
	unsigned int VAO;


	void Setup();
	void Render(Transform transform);
	void CleanUp();

private:
	unsigned int VBO, EBO;


};