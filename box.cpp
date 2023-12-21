#include "box.h"

void Box::setupBox()
{
	glGenVertexArrays(1, &VAO);

	unsigned int VBO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertex_box.size() * sizeof(glm::vec3), &vertex_box[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_box.size() * sizeof(unsigned int), &indices_box[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Box::Box(float min_x, float max_x, float min_y, float max_y, float min_z, float max_z) :
	min_x(min_x), max_x(max_x), min_y(min_y), max_y(max_y), min_z(min_z), max_z(max_z)
{
	glm::vec3 vertex_tmp;
	vertex_tmp = glm::vec3(min_x, max_y, max_z);
	vertex_box.push_back(vertex_tmp);
	vertex_tmp = glm::vec3(max_x, max_y, max_z);
	vertex_box.push_back(vertex_tmp);
	vertex_tmp = glm::vec3(max_x, max_y, min_z);
	vertex_box.push_back(vertex_tmp);
	vertex_tmp = glm::vec3(min_x, max_y, min_z);
	vertex_box.push_back(vertex_tmp);
	vertex_tmp = glm::vec3(min_x, min_y, max_z);
	vertex_box.push_back(vertex_tmp);
	vertex_tmp = glm::vec3(max_x, min_y, max_z);
	vertex_box.push_back(vertex_tmp);
	vertex_tmp = glm::vec3(max_x, min_y, min_z);
	vertex_box.push_back(vertex_tmp);
	vertex_tmp = glm::vec3(min_x, min_y, min_z);
	vertex_box.push_back(vertex_tmp);

	// Define the indices for a unit cube
	unsigned int indices[] = {
		0, 1, 3, 1, 2, 3,
		0, 3, 7, 0, 4, 7,
		0, 1, 5, 0, 4, 5,
		1, 2, 6, 1, 5, 6,
		2, 3, 7, 2, 6, 7,
		4, 5, 6, 4, 6, 7
	};
	unsigned int numIndices = sizeof(indices) / sizeof(indices[0]);
	indices_box.clear();
	for (unsigned int i = 0; i < numIndices; ++i)
	{
		indices_box.push_back(indices[i]);
	}

	setupBox();
}

void Box::Draw(Shader& shader)
{
	glBindVertexArray(VAO);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, indices_box.size(), GL_UNSIGNED_INT, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(0);
}
