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

void Scene::setupTumbler()
{
	//tumbler = Model("model/tumbler/tumbler.obj");
	num_of_tumbler = 5;
	float scale_factor = 2.5f;  // 可以根据需要调整缩放因子

	////set tumbler model matrices
	//tumbler_model_matrices.clear();
	//tumbler_model_matrices.clear();
	//tumbler_model_matrices.push_back(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, y_move, 0.0f)), glm::vec3(scale_factor)));
	//tumbler_model_matrices.push_back(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, y_move, 0.5f)), glm::vec3(scale_factor)));
	//tumbler_model_matrices.push_back(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(1.2f, y_move, -0.45f)), glm::vec3(scale_factor)));
	//tumbler_model_matrices.push_back(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, y_move, 0.5f)), glm::vec3(scale_factor)));
	//tumbler_model_matrices.push_back(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, y_move, -0.4f)), glm::vec3(scale_factor)));
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
	setupTumbler();
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

