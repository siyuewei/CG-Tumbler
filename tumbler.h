#pragma once
#include "model.h"

class Tumbler
{
private:
	glm::vec3 origin_position;
	glm::vec3 position;
	glm::vec3 axis_rotation;
	float angle;
	float scale;
public:
	Model model;

	Tumbler();

	void set_position(glm::vec3 position);
	void set_axis_rotation(glm::vec3 axis_rotation);
	void set_angle(float angle);
	void set_scale(float scale);
	glm::mat4 get_model_matrix();
};

