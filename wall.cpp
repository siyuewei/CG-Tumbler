#include "wall.h"



Wall::Wall(std::vector<float> position, glm::vec3 color)
{
	this->position = position;
	this->color = color;
	this->texture_id = -1;
	this->tex_coords = std::vector<float>(0);
	setup();
}

Wall::Wall(std::vector<float> position, std::vector<float> tex_coords, unsigned int texture_id)
{
	this->position = position;	
	this->tex_coords = tex_coords;
	this->texture_id = texture_id;
	this->color = glm::vec3(1.0f, 1.0f, 1.0f);
	setup();
}

void Wall::setup()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, position.size() * sizeof(float) + tex_coords.size() * sizeof(float), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, position.size() * sizeof(float), &position[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	if (tex_coords.size() > 0) {
		glBufferSubData(GL_ARRAY_BUFFER, position.size() * sizeof(float), tex_coords.size() * sizeof(float), &tex_coords[0]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(position.size() * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
	glBindVertexArray(0);
}

void Wall::Draw(Shader& shader)
{
	shader.use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(1.7,1.0,1.0));
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
