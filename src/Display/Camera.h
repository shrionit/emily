#ifndef CAMERA_H
#define CAMERA_H
#include <iostream>
#include <glm\glm.hpp>
#include <glm\vec3.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "GLFW\glfw3.h"
#include "..\Utils\EventManager.h"
#pragma once
class Camera {
    public:
        glm::vec3 cameraPos;
        glm::vec3 cameraTarget;
        glm::vec3 cameraDirection;
        glm::vec3 cameraUp;
        glm::vec3 cameraRight;
        glm::vec3 cameraFront;
        float deltaTime;
        float lastFrame;
        Camera(){
            defaultInit();
            updateCameraVectors();
        }
        Camera(glm::vec3 pos){
            defaultInit();
            cameraPos = pos;
            updateCameraVectors();
        }
        Camera(glm::vec3 pos, glm::vec3 target){
            defaultInit();
            cameraPos = pos;
            cameraTarget = target;
            updateCameraVectors();
        }
        void handleMovement(GLFWwindow* window){
        	if(EventManager::IsMouseKeyPressed(GLFW_MOUSE_BUTTON_MIDDLE)) handleCameraDirection(window);
            handleCameraZoom(window);
            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            const float cameraSpeed = SPEED * deltaTime; // adjust accordingly
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                cameraPos += cameraSpeed * cameraFront;
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                cameraPos -= cameraSpeed * cameraFront;
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            	cameraPos += cameraRight * cameraSpeed;
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            	cameraPos -= cameraRight * cameraSpeed;
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
				cameraPos -= cameraUp * cameraSpeed;
            if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
				cameraPos += cameraUp * cameraSpeed;
            EventManager::clearMouse();
        }
        glm::mat4x4 getViewMatrix(){
        	return glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);
        }
        void handleCameraDirection(GLFWwindow* window){
			float xoffset = EventManager::MOUSE.dpos.x;
			float yoffset = -EventManager::MOUSE.dpos.y;
			xoffset *= SENSITIVITY;
			yoffset *= SENSITIVITY;

			yaw   -= xoffset;
			pitch -= yoffset;

			if(pitch > 89.0f)
				pitch = 89.0f;
			if(pitch < -89.0f)
				pitch = -89.0f;
			updateCameraVectors();
        }
        void handleCameraZoom(GLFWwindow* window){
			fov += (float)EventManager::MOUSE.scrollY * SENSITIVITY;
			if (fov < 1.0f) fov = 1.0f;
			if (fov > 75.0f) fov = 75.0f;
			std::cout << "CAMERA::FOV = " << fov << std::endl;
        }

		float getFov() const {
			return fov;
		}

		void setFov(float fov) {
			this->fov = fov;
		}

		float getSensitivity() const {
			return SENSITIVITY;
		}

		void setSensitivity(float sensitivity) {
			SENSITIVITY = sensitivity;
		}

		float getSpeed() const {
			return SPEED;
		}

		void setSpeed(float speed) {
			SPEED = speed;
		}

    private:
        float SPEED = 2.5f;
        float SENSITIVITY = 0.1;
        float lastX = 1366/2, lastY = 768/2;
        float xpos = 0, ypos = 0;
        float yaw = 90.0, pitch = 0;
        float fov = 75;
        bool firstMouse = true;
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        void defaultInit(){
            cameraPos = glm::vec3(0.0f, 0.0f, -3.0f);
            cameraTarget = glm::vec3(0);
            cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
            deltaTime = 0.0f;
            lastFrame = 0.0f;
        }
        void updateCameraVectors() {
			// calculate the new Front vector
			glm::vec3 front;
			front.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
			front.y = glm::sin(glm::radians(pitch));
			front.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
			cameraFront = glm::normalize(front);
			// also re-calculate the Right and Up vector
			cameraRight = glm::normalize(glm::cross(cameraFront, up));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
			cameraUp    = glm::normalize(glm::cross(cameraRight, cameraFront));
		}
        glm::vec3 calcDirection(glm::vec3 pos, glm::vec3 target){
            return glm::normalize(pos - target);
        }
        glm::vec3 calcRight(glm::vec3 up, glm::vec3 dir){
            return glm::normalize(glm::cross(up, dir));
        }
        glm::vec3 calcUp(glm::vec3 dir, glm::vec3 right){
            return glm::cross(dir, right);
        }
};
#endif
