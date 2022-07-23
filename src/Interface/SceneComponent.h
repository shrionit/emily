#ifndef SCENECOMPONENT_H
#define SCENECOMPONENT_H

#include "GUI.h"
#include "../World/Scene.h"

#pragma once

class SceneComponent : public GUI {
	public:
		string label;
		SceneComponent(){
			label = "World Objects List";
			registerComponent(this);
		}

		void render();

		void setCurrentScene(EMILY::Scene& scene){
			currentScene = &scene;
		}

		EMILY::Scene* getCurrentScene(){
			return currentScene;
		}
	private:
		EMILY::Scene* currentScene = nullptr;

};

#endif