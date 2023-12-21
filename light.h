#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "shader.h"

const float PI = 3.14159265358979323846f;

const int Y_SEGMENTS = 20;
const int X_SEGMENTS = 20;

class Light
{
private:
	glm::vec3 position;
	float radius;
	glm::vec3 color;

	std::vector<glm::vec3> sphereVertices;
	std::vector<int> sphereIndices;

	void generateSphere();

public:
	unsigned int VAO;
	Light() = default;
	Light(glm::vec3 position, float radius, glm::vec3 color = glm::vec3(1.0f,1.0f,1.0f));
	void setup();
	void Draw(Shader& shader);
};

