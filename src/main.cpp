#include <iostream>
#include <functional>
#include <iterator>
#include <map>
#include <filesystem>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Display/DisplayManager.h"
#include "Shader/Shader.h"
#include "Display/Camera.h"
#include "Loader/TextureLoader.h"
#include "Utils/GMath.h"
#include "Loader/Loader.h"
#include "Interface/GUI.h"
#include "Interface/ComponentManager.h"
#include "Renderer/Renderer.h"
#include "World/Scene.h"
#include "Display/FrameBuffer.h"

float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
};

float verticesB[] = {
     0.5f,  0.5f, 0.1f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
};

float texCoords[] = {
    1.0f, 1.0f, // top-left corner
    1.0f, 0.0f,  // lower-right corner
    0.0f, 0.0f,  // top-right corner
    0.0f, 1.0f,  // lower-left corner
};

float texCoordsB[] = {
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0,
		0.0, 0.0
};

GLuint indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

int main(int argc, char* argv[]){
    Window window = DisplayManager::createWindow("OPENGL", 1366, 768);
    Shader sceneshader("shaders/scene.vs", "shaders/scene.fs");
    Shader modelShader("shaders/modelShader.vs", "shaders/modelShader.fs");
    Camera camera(glm::vec3(0,3,0), glm::vec3(0));
    EMILY::Scene scene;

    EMILY::Entity& ground = scene.createEntity("assets/models/plane/plane.obj", glm::vec3(0), glm::vec3(0), glm::vec3(100));
    EMILY::Entity& box = scene.createEntity("assets/models/cube/cube.obj", glm::vec3(0), glm::vec3(0), glm::vec3(1));
    EMILY::Entity& bag = scene.createEntity("assets/models/backpack/backpack.obj", glm::vec3(0, 5, 0), glm::vec3(0, 0, 0), glm::vec3(1));
    scene.setSelectedEntity(&bag);
    GUI::InitGUI(window.window);
    Renderer renderer(window, sceneshader, camera);
    ComponentManager::SCENE->setCurrentScene(scene);
    ComponentManager::ENTITY->setSelectedEntity(bag);
    ComponentManager::CAMERA->setSelectedCamera(camera);
    renderer.prepare();
    window.clear(0.3, 0.3, 0.3, 1.0);
	bool show_demo_window = true;
    while(!window.closed()) {
    	renderer.refresh();
        renderer.render(ground, modelShader);
        renderer.render(box, modelShader);
        renderer.render(bag, modelShader);
        GUI::renderGUI();
        window.update();
    }
    GUI::closeGUI();
    window.close();
    return 0;
}
