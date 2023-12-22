
#pragma once

#include <vector>
#include "wall.h"
#include"light.h"
#include "tumbler.h"
#include "ball.h"
#include "utils.h"

class Scene
{
private:
	std::vector<Wall> walls;
	Light light;
	std::vector<Tumbler> tumblers;
	std::vector<Ball> balls;

	unsigned int num_of_tumbler;
	std::vector<glm::mat4> tumbler_model_matrices;
	unsigned int num_of_ball;
	std::vector<glm::mat4> ball_model_matrices;

	void setupWalls();
	void setupLight();
	void setupTumblers();
	void setupBalls();

	unsigned int ball_VAO; // vertex array object

public:
	Scene();
	void DrawWalls(Shader& shader);
	void DrawLight(Shader& shader);
	void DrawTumblers(Shader& shader);
	void DrawBalls(Shader& shader);
};

