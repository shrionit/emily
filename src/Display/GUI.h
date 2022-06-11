#ifndef GUI_H
#define GUI_H
#pragma once

#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw.h"
#include "imgui\imgui_impl_opengl3.h"
#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "..\Entity\Entity.h"
#include <iostream>
#include <vector>
#include <map>
using namespace ImGui;
class EntityComponent;
class GUI {
	public:
		static GLFWwindow* window;
		GUI(){}
		GUI(GUI* c){
			components.push_back(c);
		}
		virtual ~GUI(){}
		virtual void render(){};
		static void InitGUI(GLFWwindow* win){
			window = win;
			IMGUI_CHECKVERSION();
			ImGuiContext* ctx = CreateContext();
			SetCurrentContext(ctx);
			ImGuiIO& io = GetIO(); (void)io;
			StyleColorsDark();
			InitFrame();
		}
		static void InitFrame(){
			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init("#version 400");
		}
		static void closeFrame(){
			ImGui_ImplGlfw_Shutdown();
			ImGui_ImplOpenGL3_Shutdown();
			DestroyContext();
		}
		static void renderGUI(){
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			NewFrame();
			for(auto* e : components){
				e->render();
			}
			Render();
			ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());// @suppress("Invalid arguments")
		}
	private:
		template <typename T>;
		static std::vector<T*> components;
};

GLFWwindow* GUI::window;
template<typename T>;
std::vector<T*> GUI::components;

struct FillMode {
	char* name;
	GLuint mode;
	int value;
	static std::map<int, GLuint> modes;
	FillMode(char* modeName, GLuint mode, int value){
		name = modeName;
		this->mode = mode;
		this->value = value;
		modes.insert(std::make_pair(value, mode));
	}
	static GLuint getMode(int n){
		return modes[n];
	}
};

std::map<int, GLuint> FillMode::modes;

class EntityComponent : GUI{

	public:
		float position[3];
		float rotation[3];
		float scale[3];
		int drawModeNumber;
		bool visible;
		string label;

		EntityComponent(){
			label = "Entity Properties";
			fillModes.push_back(FillMode("FILL", GL_FILL, 0));
			fillModes.push_back(FillMode("WIRE", GL_LINE, 1));
			fillModes.push_back(FillMode("VERTEX", GL_POINT, 2));
			drawModeNumber = 0;
			visible = true;
			GUI(*this);
		}

		void dummy(){
			cout << "hello world\n";
		}

		void render(){
			Begin(label.c_str());
			Checkbox("Show", &visible);
			BeginGroup();
			LabelText("Draw Mode", " IDK ");
			for(auto e : fillModes){
				RadioButton(e.name, &drawModeNumber, e.value);
			}
			cout<< "here i m\n";
			EndGroup();
			InputFloat3("Position", position, "%.4f", 0);
			InputFloat3("Rotation", rotation, "%.4f", 0);
			InputFloat3("Scale", scale, "%.4f", 0);
			End();
			selectedEntity->setPosition(getPosition());
			selectedEntity->setRotation(getRotation());
			selectedEntity->setScale(getScale());
			selectedEntity->setVisible(isVisible());
			selectedEntity->setDrawMode(FillMode::getMode(drawModeNumber));

		}

		EMILY::Entity* getSelectedEntity() {
			return selectedEntity;
		}

		void setSelectedEntity(Entity* entity){
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
		static EMILY::Entity* selectedEntity;
		static vector<FillMode> fillModes;
};
Entity* EntityComponent::selectedEntity = nullptr;
vector<FillMode> EntityComponent::fillModes;

class ComponentManager {
	public:
		static GUI ENTITY;
		static void Init(){
			ENTITY = EntityComponent();
		}
};

GUI ComponentManager::ENTITY;


#endif
