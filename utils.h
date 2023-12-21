#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "camera.h"

// settings
extern const unsigned int SCR_WIDTH;
extern const unsigned int SCR_HEIGHT;

// camera
extern glm::vec3 camPos;
extern glm::vec3 camTarget;
extern glm::vec3 camFront;
extern glm::vec3 worldUp;
extern Camera camera;
extern float lastX;
extern float lastY;
extern bool firstMouse;

// timing
extern float deltaTime;
extern float lastFrame;

// lighting
extern glm::vec3 lightPos;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

std::vector<float> ReadVerticesFromFile(const std::string& filename);

unsigned int loadTexture(char const * file_path);
unsigned int loadCubemap(std::vector<std::string> faces);