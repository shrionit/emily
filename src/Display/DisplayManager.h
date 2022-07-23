#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H
#include <functional>
#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "..\Utils\EventManager.h"

#pragma once
class Window {
    public:
        GLFWwindow* window;
        GLuint width;
        GLuint height;
        const char* title;
        Window(){}
        Window(GLFWwindow* win, int w, int h, const char* title){
            window = win;
            width = w;
            height = h;
            this->title = title;
        }
        void setOnWindowResize(GLFWframebuffersizefun cbFun=NULL){
            glfwSetFramebufferSizeCallback(window, cbFun);
        }
        void clear(float r, float g, float b, float a){
            glClearColor(r,g,b,a);
        }
        void close(){
            glfwTerminate();
        }
        void handleEvent(void(*func)(GLFWwindow* window)){
        	func(window);
        }
        bool closed(){
            return glfwWindowShouldClose(window);
        }
        void update(){
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
};

class DisplayManager {
    public:
        DisplayManager();
        ~DisplayManager();
        static Window createWindow(const char* title, int width, int height);

    private:

};

#endif
