#include <iostream>
#include <functional>
#include <iterator>
#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "Shader\Shader.h"
#include "Loader\TextureLoader.h"
#include "Display\DisplayManager.h"
#include "Display\Camera.h"
#include "Display\GUI.h"
#include <map>
#include "Utils\GMath.h"
#include "Utils\EventManager.h"
#include "Loader\Loader.h"
#include "Renderer\Renderer.h"
#include "Display\FrameBuffer.h"

void onClose(GLFWwindow* w){
    glfwSetWindowShouldClose(w, true);
}

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
    GUI::InitGUI(window.window);
    EventManager::Init(window.window);
    Shader sceneshader("shaders/scene.vs", "shaders/scene.fs");
    Shader modelShader("shaders/modelShader.vs", "shaders/modelShader.fs");
    Camera camera(glm::vec3(0,-3,-4));
    Renderer renderer(window, sceneshader, camera);
    EventManager::AddEvent(GLFW_KEY_ESCAPE, onClose);
    FrameBuffer fb(window);

    EMILY::Texture texture = EMILY::TextureLoader::load("pic.jpg");
    EMILY::Texture textureB = EMILY::TextureLoader::load("pic0.jpg");
    EMILY::Texture textureC = EMILY::TextureLoader::load("tile.jpg");

    EMILY::Entity A = Loader::loadRawModeToEntity(
    		texture,
			RawData<float>{vertices, sizeof(vertices)},
			RawData<float>{texCoords, sizeof(texCoords)},
			RawData<GLuint>{indices, sizeof(indices)}
	);
    EMILY::Entity B = Loader::loadRawModeToEntity(
			textureB,
			RawData<float>{verticesB, sizeof(verticesB)},
			RawData<float>{texCoordsB, sizeof(texCoordsB)},
			RawData<GLuint>{indices, sizeof(indices)}
	);
    EMILY::Entity ground = Loader::loadRawModeToEntity(
			textureC,
			RawData<float>{vertices, sizeof(vertices)},
			RawData<float>{texCoords, sizeof(texCoords)},
			RawData<GLuint>{indices, sizeof(indices)}
	);
    EMILY::Entity bag("assets/models/backpack.obj", glm::vec3(0, -1.5, 5), glm::vec3(90, 180, 0));
    ComponentManager::ENTITY.setSelectedEntity(&bag);
    fb.init();
    A.setPosition(glm::vec3(-1, -0.5, 3));
    B.setPosition(glm::vec3(1, -0.5, 3));
    ground.setRotation(glm::vec3(90, 0, 0));
    ground.setScale(glm::vec3(50.0));
    EMILY::Texture fbTex = EMILY::Texture(fb.depthTextureID, GL_TEXTURE0, window.width, window.height, 3);


    renderer.prepare();
    B.setTexture(fbTex);

    window.clear(0.3, 0.3, 0.3, 1.0);

    while(!window.closed()) {
        window.handleEvent(EventManager::ProcessEvents);
    	renderer.refresh();
    	fb.bind();
    	renderer.clear();
        renderer.render(A);
        fb.unBind();
        renderer.render(A);
        renderer.render(B);
        renderer.render(bag, modelShader);
        renderer.render(ground);
        GUI::renderGUI();
        window.update();
    }
    GUI::closeFrame();
    window.close();

    return 0;
}
