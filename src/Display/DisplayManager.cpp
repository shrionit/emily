#include "DisplayManager.h"
#include <iostream>
void __defaultResizeCB(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
DisplayManager::DisplayManager() {}

DisplayManager::~DisplayManager() {}

Window DisplayManager::createWindow(const char* title, int width, int height){
    if(!glfwInit()){
        std::cout << "Failed to initialize GLFW." << std::endl;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    glViewport(0, 0, width, height);
    Window w(window, width, height, title);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    w.setOnWindowResize(__defaultResizeCB);
    return w;
}
