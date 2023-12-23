#pragma once
#include "model.h"

enum Direction
{
	//顺时针
	CLOCKWISE,
	//逆时针
	COUNTERCLOCKWISE
};

class Tumbler
{
private:
	glm::vec3 origin_position;
	glm::vec3 axis_rotation;
	float angle;
	float scale;

	//速度和角速度
	glm::vec3 velocity;
	float angular_velocity;
	Direction direction;


public:
	Model model;

	glm::vec3 position;
	float max_angular_velocity;

	bool is_last_mouse_interact;
	glm::vec3 last_mouse_position;

	Tumbler();

	void set_position(glm::vec3 position);
	void set_axis_rotation(glm::vec3 axis_rotation);
	void set_angle(float angle);
	void set_scale(float scale);
	glm::mat4 get_model_matrix();

	void handle_mouse_move(glm::vec3 mouse_position,bool is_mouse = false);
	void update(float deltatime);
};

