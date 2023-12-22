#include "ball.h"

Ball::Ball(glm::vec3 position)
{
	this->origin_position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->position = position;
	this->color = glm::vec3(1.0f, 1.0f, 1.0f);
	this->texture_id = -1;
	this->radius = 1.0f;
}

void Ball::set_position(glm::vec3 position)
{
	this->position = position;
}


void Ball::set_radius(float radius)
{
	this->radius = radius;
}

glm::mat4 Ball::get_model_matrix()
{
	glm::mat4 model_matrix = glm::mat4(1.0f);
	model_matrix = glm::translate(model_matrix, this->position);
	return model_matrix;
}
