#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Ball
{
private:
	glm::vec3 origin_position;
	glm::vec3 position;

	float radius;

public:
	glm::vec3 color;
	unsigned int texture_id; //-1 表示无纹理
	Ball(glm::vec3 position);

	void set_position(glm::vec3 position);
	void set_radius(float radius);
	glm::mat4 get_model_matrix();
};

