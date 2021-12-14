#ifndef CUBE_HPP
#define CUBE_HPP

#include "Graphics/Objects/Model.h"
#include "FilePaths.h"
#include "Graphics/Rendering/Material.h"

class Cube : public Model {
public:
	glm::vec3 pos;
	glm::vec3 size;

	Material material;

	Cube() {}

	Cube(Material material, glm::vec3 pos, glm::vec3 size)
		:material(material), pos(pos), size(size) {}

	void Initialize() {
		int numbOfVertices = 36;

		float vertices[] = {
			//positions					normal				textcoords
			-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,	-1.0f,	  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,	0.0f, 0.0f,	-1.0f,	  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,	0.0f, 0.0f,	-1.0f,	  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,	0.0f, 0.0f,	-1.0f,	  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,	0.0f, 0.0f,	-1.0f,	  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,	-1.0f,	  0.0f, 0.0f,
														  
			-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,	 1.0f,	  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,	0.0f, 0.0f,	 1.0f,	  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,	0.0f, 0.0f,	 1.0f,	  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,	0.0f, 0.0f,	 1.0f,	  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,	0.0f, 0.0f,	 1.0f,	  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,	 1.0f,	  0.0f, 0.0f,
														  
			-0.5f,  0.5f,  0.5f,	-1.0f, 0.0f, 0.0f,	  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,	-1.0f, 0.0f, 0.0f,	  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,	-1.0f, 0.0f, 0.0f,	  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,	-1.0f, 0.0f, 0.0f,	  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,	-1.0f, 0.0f, 0.0f,	  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,	-1.0f, 0.0f, 0.0f,	  1.0f, 0.0f,
														  
			 0.5f,  0.5f,  0.5f,	+1.0f, 0.0f, 0.0f,	  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,	+1.0f, 0.0f, 0.0f,	  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,	+1.0f, 0.0f, 0.0f,	  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,	+1.0f, 0.0f, 0.0f,	  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,	+1.0f, 0.0f, 0.0f,	  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,	+1.0f, 0.0f, 0.0f,	  1.0f, 0.0f,
														  
			-0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,	  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,	  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,	0.0f, -1.0f, 0.0f,	  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,	0.0f, -1.0f, 0.0f,	  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,	0.0f, -1.0f, 0.0f,	  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,	  0.0f, 1.0f,
														  
			-0.5f,  0.5f, -0.5f,	0.0f, +1.0f, 0.0f,	  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,	0.0f, +1.0f, 0.0f,	  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,	0.0f, +1.0f, 0.0f,	  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,	0.0f, +1.0f, 0.0f,	  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,	0.0f, +1.0f, 0.0f,	  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,	0.0f, +1.0f, 0.0f,	  0.0f, 1.0f
		};

		std::vector<unsigned int> indices(numbOfVertices);
		for (unsigned int i = 0; i < numbOfVertices; i++) {
			indices[i] = i;
		}

		std::string tex0Path = FilePath::ImagePath + "image3.jpg";
		Texture tex0(tex0Path.c_str(), "material.diffuse");
		tex0.Load();

		std::string tex1Path = FilePath::ImagePath + "image3_specular.png";
		Texture tex1(tex1Path.c_str(), "material.specular");
		tex1.Load();

		meshes.push_back(Mesh(Vertex::SetVertices(vertices, numbOfVertices), indices, { tex0, tex1 }));
	}

	void Render(Shader shader) {
		glm::mat4 model = glm::mat4(1.0f);

		model = glm::translate(model, pos);
		//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(90.0f), glm::vec3(0.5f));
		model = glm::scale(model, size);


		shader.SetMat4("model", model);
		shader.SetMaterial(material);


		Model::Render(shader);
	}
};

#endif