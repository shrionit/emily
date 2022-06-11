#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include <functional>
#include <iostream>
#include "glm\glm.hpp"
#include "glm\vec2.hpp"
#include <map>
#include "GLFW\glfw3.h"
#pragma once

using namespace glm;
struct Mouse{
	vec2 pos = vec2(0);
	vec2 dpos = vec2(0);
	double scrollX;
	double scrollY;
};

class EventManager {
    public:
		static Mouse MOUSE;
		static void Init(GLFWwindow* window);
        static void AddEvent(GLuint key, void(*cb)(GLFWwindow* window));
        static void ProcessEvents(GLFWwindow* window);
        static void clearMouse(){
        	MOUSE.scrollX = 0;
        	MOUSE.scrollY = 0;
        	MOUSE.dpos.x=0;
        	MOUSE.dpos.y=0;
        }
        static bool IsPressed(int key){
        	return KEYS[key];
        }
        static bool IsMouseKeyPressed(int key){
        	return MOUSEKEYS[key];
        }
    private:
        static void handleMouseEvents(GLFWwindow* window, double xpos, double ypos);
        static void handleScrollEvents(GLFWwindow* window, double xoffset, double yoffset);
        static void handleKeyEvents(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void handleMouseKeyEvents(GLFWwindow* window, int button, int action, int mods);
        static std::map<GLuint, void(*)(GLFWwindow* window)> events;
        static bool KEYS[720];
        static bool MOUSEKEYS[10];
};

#endif
