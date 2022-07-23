#ifndef SCENE_H
#define SCENE_H

#pragma once
#include <string>
#include <map>
#include <memory>
#include <iostream>
#include <glm/vec4.hpp>
#include "../Entity/Entity.h"
#include "../Display/Camera.h"
#include "../Display/DisplayManager.h"
#include "../Loader/TextureLoader.h"

using namespace glm;
using namespace std;

namespace EMILY {
	class Scene {
		public:
			Scene(){};
			Scene(Window& window, Camera& camera, Shader& shader);

			Camera& createCamera(vec3 pos=vec3(0, 1, 1), vec3 target=vec3(0)){
				Camera* cam = new Camera(pos, target);
				cameras.insert(pair<string, Camera*>(cam->getID(), cam));
				return *cam;
			}

			Entity& createEntity(const char* modelPath, vec3 pos=vec3(0, 0, 0), vec3 rot=vec3(0), vec3 scale=vec3(1)){
				Entity* e = new Entity(modelPath, pos, rot, scale);
				entities.insert(pair<string, Entity*>(e->getID(), e));
				return *e;
			}

			Entity& createEntity(const char* modelPath, Texture& tex, vec3 pos=vec3(0, 0, 0), vec3 rot=vec3(0), vec3 scale=vec3(1)){
				Entity* e = new Entity(modelPath, pos, rot, scale);
				e->setTexture(tex);
				entities.insert(pair<string, Entity*>(e->getID(), e));
				return *e;
			}

			Shader& createShader(const char* vertexShaderPath, const char* fragmentShaderPath){
				Shader* shader = new Shader(vertexShaderPath, fragmentShaderPath);
				shaders.insert(pair<string, Shader*>(shader->getID(), shader));
				return *shader;
			}

			const map<string, Entity*>& getEntities(){ return entities; }
			const map<string, Camera*>& getCameras(){ return cameras; }
			const map<string, Shader*>& getShaders(){ return shaders; }

			Camera* getSelectedCamera() const {
				return selectedCamera;
			}

			void setSelectedCamera(Camera *selectedCamera) {
				this->selectedCamera = selectedCamera;
			}

			Entity* getSelectedEntity() const {
				return selectedEntity;
			}

			void setSelectedEntity(Entity *selectedEntity){
				this->selectedEntity = selectedEntity;
			}

			Shader* getSelectedShader() const {
				return selectedShader;
			}

			void setSelectedShader(Shader *selectedShader) {
				this->selectedShader = selectedShader;
			}

		private:
			static const Window window;
			Camera* selectedCamera;
			Entity* selectedEntity;
			Shader* selectedShader;
			map<string, Camera*> cameras;
			map<string, Entity*> entities;
			map<string, Shader*> shaders;
	};
}

#endif
