#include "scene.h"

void Scene::setupWalls()
{
	//5个面，3个墙面（分别呈现不同颜色），1个天花板（灰白色）和1个木纹地板
	//墙面
	//back wall : blue
	std::vector<float> position = {
		-1.0f, -1.0f, -1.0f, // bottom-left
		1.0f, 1.0f, -1.0f, // top-right
		1.0f, -1.0f, -1.0f, // bottom-right         
		1.0f, 1.0f, -1.0f, // top-right
		-1.0f, -1.0f, -1.0f, // bottom-left
		-1.0f, 1.0f, -1.0f // top-left
	};
	Wall back_wall(position, glm::vec3(0.0f, 0.0f, 1.0f));

	//left wall : green
	position = {
		-1.0f, -1.0f, 1.0f, // bottom-left
		-1.0f, 1.0f, -1.0f, // top-right
		-1.0f, -1.0f, -1.0f, // bottom-right         
		-1.0f, 1.0f, -1.0f, // top-right
		-1.0f, -1.0f, 1.0f, // bottom-left
		-1.0f, 1.0f, 1.0f // top-left
	};
	Wall left_wall(position, glm::vec3(0.0f, 1.0f, 0.0f));

	//right wall : yellow
	position = {
		1.0f, -1.0f, -1.0f, // bottom-left
		1.0f, 1.0f, 1.0f, // top-right
		1.0f, -1.0f, 1.0f, // bottom-right         
		1.0f, 1.0f, 1.0f, // top-right
		1.0f, -1.0f, -1.0f, // bottom-left
		1.0f, 1.0f, -1.0f // top-left
	};
	Wall right_wall(position, glm::vec3(1.0f, 1.0f, 0.0f));

	//floor : 木纹地板
	position = {
		-1.0f, -1.0f, -1.0f, // bottom-left
		1.0f, -1.0f, 1.0f, // top-right
		1.0f, -1.0f, -1.0f, // bottom-right         
		1.0f, -1.0f, 1.0f, // top-right
		-1.0f, -1.0f, -1.0f, // bottom-left
		-1.0f, -1.0f, 1.0f // top-left
	};
	std::vector<float> tex_coords = {
		0.0f, 0.0f, // bottom-left
		1.0f, 1.0f, // top-right
		1.0f, 0.0f, // bottom-right         
		1.0f, 1.0f, // top-right
		0.0f, 0.0f, // bottom-left
		0.0f, 1.0f // top-left
	};
	unsigned int texture_id = loadTexture("texture/wood.jpg");
	Wall floor(position, tex_coords, texture_id);

	//ceiling : 灰白色
	position = {
		-1.0f, 1.0f, 1.0f, // bottom-left
		1.0f, 1.0f, -1.0f, // top-right
		1.0f, 1.0f, 1.0f, // bottom-right         
		1.0f, 1.0f, -1.0f, // top-right
		-1.0f, 1.0f, 1.0f, // bottom-left
		-1.0f, 1.0f, -1.0f // top-left
	};
	Wall ceiling(position, glm::vec3(0.5f, 0.5f, 0.5f));

	walls.push_back(back_wall);
	walls.push_back(left_wall);
	walls.push_back(right_wall);
	walls.push_back(floor);
	walls.push_back(ceiling);

}

void Scene::setupLight()
{
	light = Light(glm::vec3(0.0f, 1.0f, 0.0f), 0.4f);
}

void Scene::setupBalls()
{
	num_of_ball = 30;
	float radius = 0.1f;
	for(unsigned int i = 0; i < num_of_ball; i++)
	{
		//生成随机位置(三个轴范围是(-1.7f + radius ,1.7f - radius),(-1.0f + radius,1.0f - radius),(-1.0f + radius,1.0f - radius))
		float x = (float)rand() / RAND_MAX * 3.4f - 1.7f + radius;
		float y = (float)rand() / RAND_MAX * 2.0f - 1.0f + radius;
		float z = (float)rand() / RAND_MAX * 2.0f - 1.0f + radius;
		glm::vec3 position = glm::vec3(x, y, z);

		Ball ball = Ball(position);
		balls.push_back(ball);
	}


	std::vector<glm::vec3> sphereVertices;
	std::vector<glm::vec2> sphereTexCoords;
	std::vector<int> sphereIndices;
	sphereVertices.clear();
	sphereIndices.clear();
	sphereTexCoords.clear(); // Clear texture coordinates vector

	glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);

	// 生成球的顶点和纹理坐标
	for (int y = 0; y <= Y_SEGMENTS; y++)
	{
		for (int x = 0; x <= X_SEGMENTS; x++)
		{
			float xSegment = (float)x / (float)X_SEGMENTS;
			float ySegment = (float)y / (float)Y_SEGMENTS;
			float xPos = center.x + radius * std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			float yPos = center.y + radius * std::cos(ySegment * PI);
			float zPos = center.z + radius * std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

			glm::vec3 vertex = glm::vec3(xPos, yPos, zPos);
			sphereVertices.push_back(vertex);

			// Calculate spherical texture coordinates
			float u = xSegment;
			float v = ySegment;
			sphereTexCoords.push_back(glm::vec2(u, v));
		}
	}

	// 生成球的Indices
	for (int i = 0; i < Y_SEGMENTS; i++)
	{
		for (int j = 0; j < X_SEGMENTS; j++)
		{
			sphereIndices.push_back(i * (X_SEGMENTS + 1) + j);
			sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j);
			sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);
			sphereIndices.push_back(i * (X_SEGMENTS + 1) + j);
			sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);
			sphereIndices.push_back(i * (X_SEGMENTS + 1) + j + 1);
		}
	}
	
	glGenVertexArrays(1, &ball_VAO);
	glBindVertexArray(ball_VAO);

	unsigned int VBO, EBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//将顶点数据绑定至当前默认的缓冲中
	glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(glm::vec3) + sphereTexCoords.size() * sizeof(glm::vec2), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sphereVertices.size() * sizeof(glm::vec3), &sphereVertices[0]);
	glBufferSubData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(glm::vec3), sphereTexCoords.size() * sizeof(glm::vec2), &sphereTexCoords[0]);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices.size() * sizeof(int), &sphereIndices[0], GL_STATIC_DRAW);

	//设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(sphereVertices.size() * sizeof(glm::vec3)));
	glEnableVertexAttribArray(1);

	//解绑VAO和VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Scene::setupTumblers()
{
	num_of_tumbler = 5;
	float scale_factor = 2.5f;  // 可以根据需要调整缩放因子
	for(unsigned int i = 0; i < num_of_tumbler; i++)
	{
		Tumbler tumbler = Tumbler();
		tumblers.push_back(tumbler);
		tumblers[i].set_scale(scale_factor);
	}
	float y_move = ( - 1.0 - tumblers[0].model.box.min_y * scale_factor)/scale_factor;

	tumblers[0].set_position(glm::vec3(0.0f / scale_factor, y_move, 0.0f / scale_factor));
	tumblers[1].set_position(glm::vec3(1.0f / scale_factor, y_move, 0.5f / scale_factor));
	tumblers[2].set_position(glm::vec3(1.2f / scale_factor, y_move, -0.45f / scale_factor));
	tumblers[3].set_position(glm::vec3(-1.0f / scale_factor, y_move, 0.5f / scale_factor));
	tumblers[4].set_position(glm::vec3(-1.0f / scale_factor, y_move, -0.4f / scale_factor));
}

Scene::Scene()
{
	setupWalls();
	setupLight();
	setupTumblers();
	setupBalls();
}

void Scene::DrawWalls(Shader& shader)
{
	for (int i = 0; i < walls.size(); i++) {
		walls[i].Draw(shader);
	}
}

void Scene::DrawLight(Shader& shader)
{
	light.Draw(shader);
}

void Scene::DrawTumblers(Shader& shader)
{
	shader.use();
	tumbler_model_matrices.clear();
	for (unsigned int i = 0; i < num_of_tumbler; i++)
	{
		tumbler_model_matrices.push_back(tumblers[i].get_model_matrix());
	}
	shader.setMatrix4fArray("modelMatrixs", num_of_tumbler, tumbler_model_matrices.data());

	for (unsigned int i = 0; i < tumblers[0].model.meshes.size(); i++)
	{
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;
		for (unsigned int j = 0; j < tumblers[0].model.meshes[i].textures.size(); j++)
		{
			glActiveTexture(GL_TEXTURE0 + j); // active proper texture unit before binding
			// retrieve texture number (the N in diffuse_textureN)
			string number;
			string name = tumblers[0].model.meshes[i].textures[j].type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++); // transfer unsigned int to string
			else if (name == "texture_normal")
				number = std::to_string(normalNr++); // transfer unsigned int to string
			else if (name == "texture_height")
				number = std::to_string(heightNr++); // transfer unsigned int to string

			// now set the sampler to the correct texture unit
			glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), j);
			// and finally bind the texture
			glBindTexture(GL_TEXTURE_2D, tumblers[0].model.meshes[i].textures[j].id);
		}

		glBindVertexArray(tumblers[0].model.meshes[i].VAO);
		glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(tumblers[0].model.meshes[i].indices.size()), GL_UNSIGNED_INT, 0, num_of_tumbler);
		glBindVertexArray(0);
	}
}

void Scene::DrawBalls(Shader& shader)
{
	shader.use();

	ball_model_matrices.clear();
	for(unsigned int i = 0; i < num_of_ball; i++)
	{
		glm::mat4 model = balls[i].get_model_matrix();
		ball_model_matrices.push_back(model);
	}
	shader.setMatrix4fArray("modelMatrixs", num_of_ball, ball_model_matrices.data());

	//ball color & texture

	std::vector<glm::vec3> ball_colors;
	std::vector<int> use_textures;  // 修改为 std::vector<int>
	std::vector<unsigned int> textures;
	bool has_texture = false;
	unsigned int texture_id = 0;
	for(unsigned int i = 0; i < num_of_ball; i++)
	{
		ball_colors.push_back(balls[i].color);
		if (balls[i].texture_id == -1) {
			use_textures.push_back(false);
		}
		else {
			has_texture = true;
			texture_id = balls[i].texture_id;
			use_textures.push_back(true);
		}
	}
	shader.setFloat3Array("ballColors", num_of_ball, ball_colors.data());
	shader.setBoolArray("useTexture", num_of_ball, reinterpret_cast<const bool*>(&use_textures[0]));

	if(has_texture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_id);
		shader.setInt("texture1", 0);
	}

	glBindVertexArray(ball_VAO);
	glDrawElementsInstanced(GL_TRIANGLES, X_SEGMENTS * Y_SEGMENTS * 6, GL_UNSIGNED_INT, 0, num_of_ball);
	glBindVertexArray(0);
}

