#include "ball.h"

Ball::Ball(glm::vec3 position, float radius)
{
	this->origin_position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->position = position;
	this->color = glm::vec3(1.0f, 1.0f, 1.0f);
	this->texture_id = -1;
	this->radius = radius;
	this->velocity = glm::vec3(0.5f, 0.0f, -0.5f);
}

void Ball::set_position(glm::vec3 position)
{
	this->position = position;
}


glm::mat4 Ball::get_model_matrix()
{
	glm::mat4 model_matrix = glm::mat4(1.0f);
	model_matrix = glm::translate(model_matrix, this->position);
	return model_matrix;
}

void Ball::update(float delta_time)
{
	//重力加速度
	glm::vec3 gravity = glm::vec3(0.0f, -1.0f, 0.0f);
	this->velocity += gravity * delta_time;

	if (position.y - (-1.0f) < radius && velocity.y < 0.1f) {
		velocity.y = 0.0;
		position.y = -1.0f + radius;
	}
	this->position += this->velocity * delta_time;
}
