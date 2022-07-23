#include "GUI.h"

GLFWwindow* GUI::window;
EMILY::EventEmitter GUI::emitter;
std::vector<GUI*> GUI::components;

void GUI::renderGUI(){
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	NewFrame();
	for(auto *e : components){
		e->render();
	}
	Render();
	ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
}
