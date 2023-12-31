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

	unsigned int ball_texture_id;
	unsigned int wall_texture_id;

	void setupWalls();
	void setupLight();
	void setupTumblers();

	unsigned int ball_VAO; // vertex array object

public:
	Scene();
	void DrawWalls(Shader& shader);
	void DrawLight(Shader& shader);
	void DrawTumblers(Shader& shader);
	void DrawBalls(Shader& shader);
	void setupBalls();

	void update(float deltatime);
	void processMouseMovement(glm::vec3 mouse_position,bool is_press);

	void check_collision();
	void check_ball_wall_collision();
};

