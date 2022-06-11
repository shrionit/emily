/*
 * Renderer.h
 *
 *  Created on: 04-Jun-2022
 *      Author: shripc
 */

#ifndef RENDERER_H
#define RENDERER_H

#include "..\Display\Camera.h"
#include "..\Display\DisplayManager.h"
#include "..\Shader\Shader.h"
#include "..\Utils\GMath.h"
#include "..\Display\GUI.h"
#include <vector>

#include "../Entity/Entity.h"

#pragma once
using namespace EMILY;
class Renderer {
	public:
		Shader shader;
		Camera camera;
		Window window;
		float fov = 75;
		float aspect = 16.0/9.0;
		float zNear = 0.1;
		float zFar = 1000.0;
		Renderer(Window& window, Shader& shader, Camera& camera){
			this->window = window;
			this->camera = camera;
			this->shader = shader;
			aspect = (float)window.width/(float)window.height;
			ComponentManager::Init();
		}
		void prepare(){
			shader.use();
			shader.setMat4("projection", GMath::projectionMatrix(fov, aspect, zNear, zFar));
			shader.detach();
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_MULTISAMPLE);
		}
		void clear(){
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		void refresh(){
			clear();
			camera.handleMovement(window.window);
		}
		void render(Entity entity){
			shader.use();
			entity.bind();
			shader.setMat4("projection", GMath::projectionMatrix(fov, aspect, zNear, zFar));
			shader.setMat4("view", camera.getViewMatrix());
			entity.render(shader);
			entity.unBind();
			shader.detach();
		}

		void render(Entity entity, Shader& newshader){
			newshader.use();
			entity.bind();
			newshader.setMat4("projection", GMath::projectionMatrix(fov, aspect, zNear, zFar));
			newshader.setMat4("view", camera.getViewMatrix());
			entity.render(newshader);
			entity.unBind();
			newshader.detach();
		}

		float getAspect() const {
			return aspect;
		}

		void setAspect(float aspect = 16.0 / 9.0) {
			this->aspect = aspect;
		}

		const Camera& getCamera() const {
			return camera;
		}

		void setCamera(const Camera &camera) {
			this->camera = camera;
		}

		float getFov() const {
			return fov;
		}

		void setFov(float fov = 75) {
			this->fov = fov;
		}

		const Shader& getShader() const {
			return shader;
		}

		void setShader(const Shader &shader) {
			this->shader = shader;
		}

		const Window& getWindow() const {
			return window;
		}

		void setWindow(const Window &window) {
			this->window = window;
		}

		float getZFar() const {
			return zFar;
		}

		void setZFar(float zFar = 1000.0) {
			this->zFar = zFar;
		}

		float getZNear() const {
			return zNear;
		}

		void setZNear(float zNear = 0.1) {
			this->zNear = zNear;
		}
};

#endif
