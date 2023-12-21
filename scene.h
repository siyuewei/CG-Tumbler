#pragma once

#include <vector>
#include "wall.h"
#include"light.h"
#include "model.h"

#include "utils.h"

class Scene
{
private:
	std::vector<Wall> walls;
	Light light;
	Model tumbler;

	unsigned int num_of_tumbler;
	std::vector<glm::mat4> tumbler_model_matrices;

	void setupWalls();
	void setupLight();
	void setupTumbler();

public:
	Scene();
	void DrawWalls(Shader& shader);
	void DrawLight(Shader& shader);
	void DrawTumblers(Shader& shader);
};

