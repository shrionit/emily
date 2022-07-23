#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include "SceneComponent.h"
#include "EntityComponent.h"
#include "CameraComponent.h"

#pragma once

class ComponentManager {
	public:
		static EntityComponent* ENTITY;
		static CameraComponent* CAMERA;
		static SceneComponent* SCENE;
		static void Init();
};

#endif