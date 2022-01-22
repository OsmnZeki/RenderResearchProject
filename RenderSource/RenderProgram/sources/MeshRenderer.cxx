#include "..\include\MeshRenderer.h"




void MeshRenderer::Setup()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind VAO
	glBindVertexArray(VAO);

	//bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), &mesh.vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), &mesh.indices[0], GL_STATIC_DRAW);


	//set vertex attribute pointers

		//vertex.textcoord
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

	//vertex.normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	//vertex.position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));


	glBindVertexArray(0);

}

void MeshRenderer::Render(Transform transform)
{
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, transform.position);
	model = glm::rotate(model, glm::radians(transform.rotation.r), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(transform.rotation.g), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(transform.rotation.b), glm::vec3(0, 0, 1));
	model = glm::scale(model, transform.size);
	
	
	material->shader->SetMat4("model", model);

	material->ConfigurationShader();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);

}


void MeshRenderer::CleanUp()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
