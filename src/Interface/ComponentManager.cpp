#include "ComponentManager.h"

EntityComponent* ComponentManager::ENTITY;
CameraComponent* ComponentManager::CAMERA;
SceneComponent* ComponentManager::SCENE;

void ComponentManager::Init(){
    ENTITY = new EntityComponent();
    CAMERA = new CameraComponent();
    SCENE = new SceneComponent();
}