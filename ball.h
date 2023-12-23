#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Ball
{
private:
	glm::vec3 origin_position;


public:
	glm::vec3 position;
	float radius;
	glm::vec3 velocity;

	glm::vec3 color;
	unsigned int texture_id; //-1 表示无纹理
	Ball(glm::vec3 position,float radius);

	void set_position(glm::vec3 position);
	glm::mat4 get_model_matrix();

	void update(float delta_time);
};

