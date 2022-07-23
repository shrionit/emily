#ifndef CAMERA_H
#define CAMERA_H
#include <iostream>
#include <string>
#include "..\utils\UUID.h"
#include <glm\glm.hpp>
#include <glm\vec3.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "GLFW\glfw3.h"
#include "..\Utils\EventManager.h"

using namespace std;
#pragma once
class Camera {
    public:

        glm::vec3 cameraPos;
        glm::vec3 cameraTarget;
        glm::vec3 cameraDirection;
        glm::vec3 cameraUp;
        glm::vec3 cameraRight;
        glm::vec3 cameraFront;
        float maxFOV = 135;
        float minFOV = 35;
        float deltaTime;
        float lastFrame;

        const std::string& getID(){
        	return ID;
        }

        const std::string getLabel(){
        	return label;
        }

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
//            float currentFrame = static_cast<float>(glfwGetTime());
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            const float cameraSpeed = SPEED * deltaTime; // adjust accordingly
            if (EventManager::IsPressed(GLFW_KEY_W))
                cameraPos += cameraSpeed * cameraFront;
            if (EventManager::IsPressed(GLFW_KEY_S))
                cameraPos -= cameraSpeed * cameraFront;
            if (EventManager::IsPressed(GLFW_KEY_A))
            	cameraPos -= cameraRight * cameraSpeed;
            if (EventManager::IsPressed(GLFW_KEY_D))
            	cameraPos += cameraRight * cameraSpeed;
            if (EventManager::IsPressed(GLFW_KEY_LEFT_SHIFT))
				cameraPos += cameraUp * cameraSpeed;
            if (EventManager::IsPressed(GLFW_KEY_LEFT_CONTROL))
				cameraPos -= cameraUp * cameraSpeed;
            EventManager::clearMouse();
        }
        glm::mat4x4 getViewMatrix(){
//        	cout << "getViewMat - Camera.cameraPos["<< hex << this <<"]: " << cameraPos.x << ", " << cameraPos.y << ", " << cameraPos.z << endl;
        	return glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);
        }
        void handleCameraDirection(GLFWwindow* window){
        	float xoffset = EventManager::MOUSE.dpos.x;
        	float yoffset = -EventManager::MOUSE.dpos.y;
			xoffset *= SENSITIVITY;
			yoffset *= SENSITIVITY;
			yaw   += xoffset;
			pitch += yoffset;
			updateCameraVectors();
        }
        void handleCameraZoom(GLFWwindow* window){
			fov -= (float)EventManager::MOUSE.scrollY * SENSITIVITY;
			if (fov < minFOV) fov = minFOV;
			if (fov > maxFOV) fov = maxFOV;
        }

		float getFov() const { return fov; }
		void setFov(float fov) { this->fov = fov; }
		float getYaw() const { return yaw; }
		void setYaw(float yaw) { this->yaw = yaw; }
		float getPitch() const { return pitch; }
		void setPitch(float pitch) { this->pitch = pitch; }
		float getSensitivity() const { return SENSITIVITY; }
		void setSensitivity(float sensitivity) { SENSITIVITY = sensitivity; }
		float getSpeed() const { return SPEED; }
		void setSpeed(float speed) { SPEED = speed; }
		glm::vec3& getCameraFront() { return cameraFront; }
		void setCameraFront(const glm::vec3 cameraFront) { this->cameraFront = cameraFront; }
        void setCameraPos(const glm::vec3 cameraPos) { this->cameraPos = cameraPos; }
		
        glm::vec3& getCameraPos() { return cameraPos; }


    private:
        string label = "Camera";
        string ID;
        float SPEED = 5.5f;
        float SENSITIVITY = 1;
        float lastX = 1366/2, lastY = 768/2;
        float xpos = 0, ypos = 0;
        float yaw = -90.0, pitch = 0;
        float fov = 75;
        bool firstMouse = true;
        void defaultInit(){
        	ID = uuid::v4();
            cameraPos = glm::vec3(0.0f, 0.0f, -3.0f);
            cameraTarget = glm::vec3(0);
            cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
            cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
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
			cameraRight = glm::normalize(glm::cross(cameraFront, glm::vec3(0,1,0)));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
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
