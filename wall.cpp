#include "wall.h"

Wall::Wall(std::vector<float> position, glm::vec3 normal,glm::vec3 color)
{
	this->position = position;
	this->color = color;
	this->texture_id = -1;
	this->tex_coords = std::vector<float>(0);
	this->normal = normal;
	this->model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(1.7, 1.0, 1.0));
	setup();
}

Wall::Wall(std::vector<float> position, glm::vec3 normal, std::vector<float> tex_coords, unsigned int texture_id)
{
	this->position = position;	
	this->tex_coords = tex_coords;
	this->texture_id = texture_id;
	this->color = glm::vec3(1.0f, 1.0f, 1.0f);
	this->normal = normal;
	this->model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(1.7, 1.0, 1.0));
	setup();
}

void Wall::setup()
{
	std::vector<glm::vec3> normals;
	for (int i = 0; i < position.size(); i += 3) {
		normals.push_back(normal);
	}

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, position.size() * sizeof(float) + tex_coords.size() * sizeof(float), NULL, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, position.size() * sizeof(float) + tex_coords.size() * sizeof(float) + normals.size() * sizeof(glm::vec3), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, position.size() * sizeof(float), &position[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBufferSubData(GL_ARRAY_BUFFER,position.size() * sizeof(float),normals.size() * sizeof(glm::vec3), &normals[0]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(position.size() * sizeof(float)));
	glEnableVertexAttribArray(1);
	if (tex_coords.size() > 0) {
		glBufferSubData(GL_ARRAY_BUFFER, position.size() * sizeof(float) + normals.size() * sizeof(glm::vec3), tex_coords.size() * sizeof(float), &tex_coords[0]);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(position.size() * sizeof(float) + normals.size() * sizeof(glm::vec3)));
		glEnableVertexAttribArray(2);
	}
	glBindVertexArray(0);
}

void Wall::Draw(Shader& shader)
{
	shader.use();
	shader.setMatrix4fv("model",1, model);
	glBindVertexArray(VAO);
	if (texture_id != -1) {
		shader.setInt("texture1", 0);
		shader.setBool("useTexture", true);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_id);
	}
	else {
		shader.setBool("useTexture", false);
		shader.setFloatVec3("color", color);
	}
	glDrawArrays(GL_TRIANGLES, 0, position.size() / 3);
	glBindVertexArray(0);
}
