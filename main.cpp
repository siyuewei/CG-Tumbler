#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "Camera.h"
#include "utils.h"
#include "main_helper.h"
#include "model.h"
#include "scene.h"
#include <iostream>
#include <vector>
#include <map>


int main() {
	//1.init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
std::cout << "Failed to create GLFW window" << std::endl;
glfwTerminate();
return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------

    //2.Shader
    Shader wallShader("shader/wall.vs", "shader/wall.fs");
    Shader lightShader("shader/light.vs", "shader/light.fs");
    Shader tumblerShader("shader/tumbler.vs", "shader/tumbler.fs");
    Shader ballShader("shader/ball.vs", "shader/ball.fs");
    
    Shader wallDepthShader("shader_depth/wall_depth.vs", "shader_depth/wall_depth.fs");
    Shader tumblerDepthShader("shader_depth/tumbler_depth.vs", "shader_depth/tumbler_depth.fs");
    Shader ballDepthShader("shader_depth/ball_depth.vs", "shader_depth/ball_depth.fs");

    scene = new Scene();

    unsigned int uboMatrices;
    glGenBuffers(1, &uboMatrices);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // define the range of the buffer that links to a uniform binding point
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 3 * sizeof(glm::mat4));
    wallShader.bindUniformBlock("Matrices", 0);
    lightShader.bindUniformBlock("Matrices", 0);
    tumblerShader.bindUniformBlock("Matrices", 0);
    ballShader.bindUniformBlock("Matrices", 0);
    wallDepthShader.bindUniformBlock("Matrices", 0);
    tumblerDepthShader.bindUniformBlock("Matrices", 0);
    ballDepthShader.bindUniformBlock("Matrices", 0);

    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    unsigned int depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);
    // create depth texture
    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
        
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        glm::mat4 lightProjection = glm::mat4(1.0f);
        glm::mat4 lightView = glm::mat4(1.0f);
        glm::mat4 lightSpaceMatrix = glm::mat4(1.0f);

        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        lightProjection = glm::perspective(glm::radians(90.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, 0.1f, 100.0f);
        lightView = glm::lookAt(lightPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        lightSpaceMatrix = lightProjection * lightView;
        
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(lightProjection));
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(lightView));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        wallDepthShader.use();
        scene->DrawWalls(wallDepthShader);
        tumblerDepthShader.use();
        scene->DrawTumblers(tumblerDepthShader);
        ballDepthShader.use();
        scene->DrawBalls(ballDepthShader);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glViewport(0, 0, 1400, 800);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        projection = glm::perspective(glm::radians(camera.getZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        view = camera.GetViewMatrix();

        glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
        glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(lightSpaceMatrix));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);


        wallShader.use();
        wallShader.setFloatVec3("lightColor", lightColor);
        wallShader.setFloatVec3("lightPos", lightPos);
        wallShader.setFloatVec3("viewPos", camera.getPosition());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        wallShader.setInt("shadowMap", 1);
        scene->DrawWalls(wallShader);

        lightShader.use();
        scene->DrawLight(lightShader);

        tumblerShader.use();
        tumblerShader.setFloatVec3("lightColor", lightColor);
        tumblerShader.setFloatVec3("lightPos", lightPos);
        tumblerShader.setFloatVec3("viewPos", camera.getPosition());
        //glActiveTexture(GL_TEXTURE1);
        //glBindTexture(GL_TEXTURE_2D, depthMap);
        //tumblerShader.setInt("shadowMap", 1);
        scene->DrawTumblers(tumblerShader);
        
		ballShader.use();
		scene->DrawBalls(ballShader);
		

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        scene->update(deltaTime);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
	return 0;
}

