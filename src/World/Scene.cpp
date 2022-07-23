#include "Scene.h"

namespace EMILY {

	Scene::Scene(Window& window, Camera& camera, Shader& shader) {
		cameras.insert(pair<string, Camera*>(camera.getID(), &camera));
	}

}
