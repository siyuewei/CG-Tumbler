#include "light.h"

void Light::generateSphere()
{
    sphereVertices.clear();
    sphereIndices.clear();

    // 生成球的顶点
    for (int y = 0; y <= Y_SEGMENTS / 2; y++)
    {
        for (int x = 0; x <= X_SEGMENTS; x++)
        {
            float xSegment = (float)x / (float)X_SEGMENTS;
            float ySegment = (float)y / (float)Y_SEGMENTS + 1;  // 调整ySegment范围
            float xPos = position.x + radius * std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            float yPos = position.y + radius * std::cos(ySegment * PI);
            float zPos = position.z + radius * std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            glm::vec3 vertex = glm::vec3(xPos, yPos, zPos);
            sphereVertices.push_back(vertex);
        }
    }

    // 生成球的Indices
    for (int i = 0; i < Y_SEGMENTS / 2; i++)
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
}


Light::Light(glm::vec3 position, float radius, glm::vec3 color)
{
	this->position = position;
	this->radius = radius;
	this->color = color;

	generateSphere();
	setup();
}

void Light::setup()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(glm::vec3), &sphereVertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(0);

}

void Light::Draw(Shader& shader)
{
	shader.use();
	shader.setFloatVec3("color", color);
    shader.setMatrix4fv("model", 1, glm::mat4(1.0f));
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, &sphereIndices[0]);
	glBindVertexArray(0);
}
