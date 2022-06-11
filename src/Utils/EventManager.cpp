/*
 * EventManager.cpp
 *
 *  Created on: 05-Jun-2022
 *      Author: shripc
 */
#include "EventManager.h"

Mouse EventManager::MOUSE;

bool EventManager::KEYS[720];
bool EventManager::MOUSEKEYS[10];

std::map<GLuint, void(*)(GLFWwindow* window)> EventManager::events;

void EventManager::Init(GLFWwindow* window){
	glfwSetKeyCallback(window, handleKeyEvents);
	glfwSetMouseButtonCallback(window, handleMouseKeyEvents);
	glfwSetCursorPosCallback(window, handleMouseEvents);
	glfwSetScrollCallback(window, handleScrollEvents);
}

void EventManager::AddEvent(GLuint key, void(*cb)(GLFWwindow* window)){
	events.insert(std::make_pair(key, cb));
}

void EventManager::ProcessEvents(GLFWwindow* window){
	std::map<GLuint, void(*)(GLFWwindow* window)>::iterator iter;
	for(iter = events.begin();iter != events.end();iter++){
		if(glfwGetKey(window, iter->first) == GLFW_PRESS){
			iter->second(window);
		}
	}
}

void EventManager::handleKeyEvents(GLFWwindow* window, int key, int scancode, int action, int mods){
	std::cout << "KEY = " << key << std::endl;
	KEYS[key] = action != GLFW_RELEASE;
}

void EventManager::handleMouseKeyEvents(GLFWwindow* window, int button, int action, int mods) {
	MOUSEKEYS[button] = action != GLFW_RELEASE;
}

void EventManager::handleMouseEvents(GLFWwindow* window, double xpos, double ypos){
	MOUSE.dpos.x = (float)xpos - MOUSE.pos.x;
	MOUSE.dpos.y = (float)ypos - MOUSE.pos.y;
	MOUSE.pos.x = (float)xpos;
	MOUSE.pos.y = (float)ypos;
}

void EventManager::handleScrollEvents(GLFWwindow* window, double xoffset, double yoffset){
	MOUSE.scrollX = xoffset;
	MOUSE.scrollY = yoffset;
}
