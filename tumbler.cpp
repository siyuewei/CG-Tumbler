#include "tumbler.h"

Tumbler::Tumbler()
{
	model = Model("model/tumbler/tumbler.obj");
	origin_position = glm::vec3(0.0f, 0.0f, 0.0f);
	position = origin_position;
	axis_rotation = glm::vec3(0.0f, 1.0f, 0.0f);
	angle = 0.0f;
	scale = 1.0f;
}

void Tumbler::set_position(glm::vec3 position)
{
	this->position = position;
}

void Tumbler::set_axis_rotation(glm::vec3 axis_rotation)
{
	this->axis_rotation = axis_rotation;
}

void Tumbler::set_angle(float angle)
{
	this->angle = angle;
}

void Tumbler::set_scale(float scale)
{
	this->scale = scale;
}

glm::mat4 Tumbler::get_model_matrix()
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(scale));
	model = glm::rotate(model, glm::radians(angle), axis_rotation);
	model = glm::translate(model, position - origin_position);
	return model;
}
