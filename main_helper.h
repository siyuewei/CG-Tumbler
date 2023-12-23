#pragma once  // 或者使用 include guards

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h"
#include "scene.h"

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

extern Scene *scene;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

glm::vec3 getWorldPosForm2D(int x, int y, glm::mat4 pro, glm::mat4 view);