#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<float> ReadVerticesFromFile(const std::string& filename);

unsigned int loadTexture(char const * file_path);
unsigned int loadCubemap(std::vector<std::string> faces);