#ifndef GMATH_H
#define GMATH_H
#pragma once
#include <glm\glm.hpp>
#include <glm\vec4.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "..\Display\Camera.h"

class GMath {
    public:
        static glm::mat4x4 transformationMatrix(glm::vec3& pos, glm::vec3& rot, glm::vec3& scale){
            glm::mat4x4 model = glm::mat4x4(1);
            model = glm::translate(model, pos);
            model = glm::rotate(model, glm::radians(rot.x), glm::vec3(1,0,0));
            model = glm::rotate(model, glm::radians(rot.y), glm::vec3(0,1,0));
            model = glm::rotate(model, glm::radians(rot.z), glm::vec3(0,0,1));
            model = glm::scale(model, scale);
            return model;
        }
        static glm::mat4x4 projectionMatrix(float& fov, float& aspect, float& zNear, float& zFar){
            return glm::perspective(glm::radians(fov), aspect, zNear, zFar);
        }
        static glm::mat4x4 viewMatrix(Camera& camera){
            return glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraFront, camera.cameraUp);
        }
};

#endif
