#ifndef ENTITYCOMPONENT_H
#define ENTITYCOMPONENT_H

#include "GUI.h"
#include "../Entity/Entity.h"
#include <iostream>
using namespace std;
#pragma once

struct FillMode {
	const char* name;
	GLuint mode;
	int value;
	static std::map<int, GLuint> modes;
	FillMode(const char* modeName, GLuint mode, int value){
		name = modeName;
		this->mode = mode;
		this->value = value;
		modes.insert(std::make_pair(value, mode));
	}
	static GLuint getMode(int n){
		return modes[n];
	}
};

class EntityComponent : public GUI {

	public:
		float position[3];
		float rotation[3];
		float scale[3];
		int drawModeNumber;
		bool visible;
		string label;

		EntityComponent(){
			label = "Entity Properties";
			fillModes.push_back(FillMode(FILL, GL_FILL, 0));
			fillModes.push_back(FillMode(WIRE, GL_LINE, 1));
			fillModes.push_back(FillMode(VERTEX, GL_POINT, 2));
			drawModeNumber = 0;
			visible = true;
			GUI::emitter.on<Entity*>([this](Entity *e){
				cout << "Event On" << endl;
				this->setSelectedEntity(*e);
			});
			registerComponent(this);
		}

		void render();

		EMILY::Entity* getSelectedEntity() {
			return selectedEntity;
		}

		void setSelectedEntity(Entity& e){
			Entity *entity = &e;
			setPosition(entity->getPosition());
			setRotation(entity->getRotation());
			setScale(entity->getScale());
			selectedEntity = entity;
		}
		GLuint getDrawMode() {
			return FillMode::getMode(drawModeNumber);
		}

		const glm::vec3 getPosition() {
			return glm::vec3(position[0], position[1], position[2]);
		}

		void setPosition(const glm::vec3 &pos) {
			position[0] = pos.x;
			position[1] = pos.y;
			position[2] = pos.z;
		}

		const glm::vec3 getRotation() {
			return glm::vec3(rotation[0], rotation[1], rotation[2]);
		}

		void setRotation(const glm::vec3 &rot) {
			rotation[0] = rot.x;
			rotation[1] = rot.y;
			rotation[2] = rot.z;
		}

		const glm::vec3 getScale() {
			return glm::vec3(scale[0], scale[1], scale[2]);
		}

		void setScale(const glm::vec3 &size) {
			scale[0] = size.x;
			scale[1] = size.y;
			scale[2] = size.z;
		}

		bool isVisible() {
			return visible;
		}

		void setVisible(bool show) {
			visible = show;
		}

	private:
		const char* FILL = "FILL";
		const char* WIRE = "WIRE";
		const char* VERTEX = "VERTEX";
		static EMILY::Entity* selectedEntity;
		static vector<FillMode> fillModes;
};

#endif