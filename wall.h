#pragma once

#include <vector>

#include "shader.h"
class Wall
{
private:
	std::vector<float> position;
	std::vector<float> tex_coords;
	unsigned int texture_id;
	glm::vec3 color;

public:
	unsigned int VAO;
	Wall(std::vector<float> position, glm::vec3 color);
	Wall(std::vector<float> position, std::vector<float> tex_coords, unsigned int texture_id);
	void setup();
	void Draw(Shader &shader);
};

