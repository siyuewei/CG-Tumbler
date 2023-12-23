#include "tumbler.h"

Tumbler::Tumbler()
{
	model = Model("model/tumbler/tumbler.obj");
	origin_position = glm::vec3(0.0f, 0.0f, 0.0f);
	position = origin_position;
	axis_rotation = glm::vec3(0.0f, 0.0f, 1.0f);
	angle = 0.0f;
	scale = 1.0f;

	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	angular_velocity = 0.0f;
	max_angular_velocity = 0.0f;
	direction = CLOCKWISE;
	is_last_mouse_interact = false;

}

void Tumbler::set_position(glm::vec3 position)
{
	this->position = position;
}

void Tumbler::set_axis_rotation(glm::vec3 axis_rotation)
{
	this->axis_rotation = axis_rotation;
}

void Tumbler::set_angle(float angle)
{
	this->angle = angle;
}

void Tumbler::set_scale(float scale)
{
	this->scale = scale;
}

glm::mat4 Tumbler::get_model_matrix()
{
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis_rotation);
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(position - origin_position));
	glm::mat4 model = translationMatrix * rotationMatrix * scaleMatrix;
	return model;
}

void Tumbler::handle_mouse_move(glm::vec3 mouse_position, bool is_mouse)
{
	//if (is_mouse) {
	//	std::cout << "pressed " << std::endl;
	//}
	//1. 0 -> 1
	if(is_last_mouse_interact == false && is_mouse == true)
	{
		std::cout << "0-> 1" << std::endl;
		//停下来
		this->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		this->angular_velocity = 0.0f;
	}

	//2. 1-> 1
	if (is_last_mouse_interact == true && is_mouse == true)
	{
		std::cout << "1-> 1" << std::endl;
		//判断是质心上面还是下面
		//质心做垂线与旋转轴相交于点A，质心与点A的连线是平面的法线，旋转轴是平面上一点
		glm::vec3 axis = glm::normalize(axis_rotation);
		glm::vec3 A = glm::dot(position, axis) * axis;
		glm::vec3 planeNormal = glm::normalize(A - position);
		glm::vec3 toMouse = mouse_position - position;
		toMouse.y -= 0.9f;
		float distanceToPlane = glm::dot(toMouse, planeNormal);

		// 判断鼠标位置是在质心上方还是下方
		if (distanceToPlane>0)
		{
			//std::cout << "上方" << std::endl;
			// 鼠标在质心上方
			float distance = glm::length(mouse_position - position);
			glm::vec3 delta_mouse = mouse_position - last_mouse_position;
			float delta_x = glm::length(delta_mouse);
			float delta_angle = glm::degrees(2 * glm::asin(delta_x / (2 * distance)));
			if (delta_mouse.x < 0) {
				angle += delta_angle * 10;
			}
			else {
				angle -= delta_angle * 10;
			}
		}
		else
		{
			// 鼠标在质心下方
			//std::cout << "下方" << std::endl;
			glm::vec3 delta_mouse = mouse_position - last_mouse_position;
			position.x += delta_mouse.x;
			position.z += delta_mouse.z;

		}
	}

	//3. 1 -> 0
	if (is_last_mouse_interact == true && is_mouse == false) {
		std::cout << "1 -> 0" << std::endl;

		this->angular_velocity = - angle * 10;
	}

	//4. 0 -> 0，不处理
	if (is_last_mouse_interact == false && is_mouse == false) {
		//std::cout << "0 -> 0" << std::endl;
	}

	//更新
	this->is_last_mouse_interact = is_mouse;
	this->last_mouse_position = mouse_position;
}

void Tumbler::update(float deltatime)
{
	//根据速度和角速度更新位置和角度
	this->position += this->velocity * deltatime;

	//根据angle更新角速度大小


	if (direction == CLOCKWISE)
	{
		this->angle += this->angular_velocity * deltatime;
	}
	else {
		this->angle -= this->angular_velocity * deltatime;
	}


	//获取旋转后最低点的y轴信息，让不倒翁抬高到地板上
	float min_y = _MM_FIXUP_MIN_FLOAT;
	for (unsigned int i = 0; i < this->model.meshes.size(); i++) {
		for (unsigned int j = 0; j < this->model.meshes[i].vertices.size(); j++) {
			glm::vec3 vertex = this->model.meshes[i].vertices[j].Position;
			vertex = glm::vec3(this->get_model_matrix() * glm::vec4(vertex, 1.0f));
			if (vertex.y < min_y) {
				min_y = vertex.y;
			}
		}
	}

	this->position.y -= min_y + 1.0f;

}
