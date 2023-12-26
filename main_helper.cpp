#include "main_helper.h"


unsigned int SCR_WIDTH = 1400;
unsigned int SCR_HEIGHT = 800;

// camera
glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.5f);
glm::vec3 camTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 camFront = glm::normalize(camTarget - camPos);
glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
Camera camera(camPos, camFront, worldUp);
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 lightPos = glm::vec3(0.0f, 0.8f, 0.0f);
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

Scene *scene = nullptr;

bool isShowBalls = false;

// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyBoard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyBoard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyBoard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyBoard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyBoard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.ProcessKeyBoard(DOWN, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
        scene->setupBalls();
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessScroll(static_cast<float>(yoffset));
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{


    if (scene == nullptr)
        return;
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    //if (firstMouse)
    //{
    //    lastX = xpos;
    //    lastY = ypos;
    //    firstMouse = false;
    //}

    //float xoffset = xpos - lastX;
    //float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    //lastX = xpos;
    //lastY = ypos;

    //camera.ProcessMouseMovement(xoffset, yoffset, false);

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    projection = glm::perspective(glm::radians(camera.getZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    view = camera.GetViewMatrix();

    glm::vec3 mouseWorldPos = getWorldPosForm2D(xpos, ypos, projection, view);
    int leftMouseButtonState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    //if (leftMouseButtonState) {
    //    std::cout << "mouse left pressed " << std::endl;
    //}

    if (leftMouseButtonState) 
        scene->processMouseMovement(mouseWorldPos, true);
    else
        scene->processMouseMovement(mouseWorldPos, false);
}


glm::vec3 getWorldPosForm2D(int x, int y, glm::mat4 pro, glm::mat4 view)
{
    // 将屏幕坐标转换为NDC（标准化设备坐标）
    float win_x = (float)x;
    float win_y = (float)SCR_HEIGHT - (float)y - 1.0f;
    float win_z;

    // 从深度缓冲区中读取深度值
    glReadBuffer(GL_BACK);
    glReadPixels(x, int(win_y), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &win_z);

    // 反投影屏幕坐标到世界坐标
    glm::vec3 winCoords(win_x, win_y, win_z);
    glm::vec4 viewport = glm::vec4(0, 0, SCR_WIDTH, SCR_HEIGHT);
    //std::cout << "mouse pos: " << win_x << " " << win_y << " " << win_z << std::endl;

    glm::vec3 obj = glm::unProject(winCoords, view, pro, viewport);

    return obj;
}

void getAllDepth()
{
    GLfloat* depthData = new GLfloat[SCR_WIDTH * SCR_HEIGHT];
    glReadPixels(0, 0, SCR_WIDTH, SCR_HEIGHT, GL_DEPTH_COMPONENT, GL_FLOAT, depthData);

    // 打印深度信息
    for (int i = 0; i < SCR_WIDTH; ++i) {
        for (int j = 0; j < SCR_HEIGHT; ++j) {
            std::cout << depthData[i * SCR_WIDTH + j] << " ";
        }
        std::cout << std::endl;
    }
}

void renderSceneDepth(const Shader& shader)
{
   
}