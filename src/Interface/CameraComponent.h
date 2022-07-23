#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H
#include "GUI.h"
#include "../Display/Camera.h"
#pragma once

class CameraComponent : public GUI {
	public:
		float cameraPos[3];
		float cameraFront[3];
		float movementSpeed=1;
		float sensitivity=1;
		float fov=45;
		float yaw=-90;
		float pitch=0;
		string label;
		CameraComponent(){
			label = "Camera Properties";
			registerComponent(this);
		}

		void render(){
			getCameraValues();
			Begin(label.c_str());
			{
				GUI::BeginGroupPanel("Camera Position", ImVec2(-1.0f, 0.0f));
				{
					BeginColumns("CameraTransformations", 2, 0);
					IMGUI_LEFT_LABEL(InputFloat("##Position X", &cameraPos[0], 0.001f, 0.05f, "%.4f", 0), "Position X");
					IMGUI_LEFT_LABEL(InputFloat("##Position Y", &cameraPos[1], 0.001f, 0.05f, "%.4f", 0), "Position Y");
					IMGUI_LEFT_LABEL(InputFloat("##Position Z", &cameraPos[2], 0.001f, 0.05f, "%.4f", 0), "Position Z");
					EndColumns();
				}
				GUI::EndGroupPanel();
				GUI::BeginGroupPanel("Camera View", ImVec2(-1.0f, 0.0f));
				{
					BeginColumns("CameraView", 2, 0);
					IMGUI_LEFT_LABEL(DragFloat("##Field Of View", &fov, 1, 45, 118, "%.3f", 0), "Field Of View");
					IMGUI_LEFT_LABEL(DragFloat("##Yaw", &yaw, 1, -90, 90, "%.3f", 0), "Yaw");
					IMGUI_LEFT_LABEL(DragFloat("##Pitch", &pitch, 1, -90, 90, "%.3f", 0), "Pitch");
					IMGUI_LEFT_LABEL(DragFloat("##Sensitivity", &sensitivity, 0.1f, 0.1f, 10.0f, "%.3f", 0), "Sensitivity");
					IMGUI_LEFT_LABEL(DragFloat("##Speed", &movementSpeed, 0.1f, 0.1f, 10.0f, "%.3f", 0), "Speed");
					EndColumns();
				}
				GUI::EndGroupPanel();
			}
			End();
			selectedCamera->setFov(getFov());
			selectedCamera->setYaw(getYaw());
			selectedCamera->setPitch(getPitch());
			selectedCamera->setSensitivity(getSensitivity());
			selectedCamera->setSpeed(getMovementSpeed());
			selectedCamera->setCameraPos(getCameraPos());
			selectedCamera->setCameraFront(getCameraFront());
		}

		Camera* getSelectedCamera() {
			return selectedCamera;
		}

		void setSelectedCamera(Camera& camera){
			selectedCamera = &camera;
			getCameraValues();
		}

		void getCameraValues(){
			setCameraPos(selectedCamera->getCameraPos());
			setCameraFront(selectedCamera->getCameraFront());
			setFov(selectedCamera->getFov());
			setPitch(selectedCamera->getPitch());
			setYaw(selectedCamera->getYaw());
			setMovementSpeed(selectedCamera->getSpeed());
			setSensitivity(selectedCamera->getSensitivity());
		}

		void setCameraPos(glm::vec3 pos){
			cameraPos[0] = pos.x;
			cameraPos[1] = pos.y;
			cameraPos[2] = pos.z;
		}

		void setCameraFront(glm::vec3 front){
			cameraFront[0] = front.x;
			cameraFront[1] = front.y;
			cameraFront[2] = front.z;
		}

		glm::vec3 getCameraFront() {
			return glm::vec3(cameraFront[0], cameraFront[1], cameraFront[2]);
		}

		glm::vec3 getCameraPos() {
			return glm::vec3(cameraPos[0], cameraPos[1], cameraPos[2]);
		}

		float getFov() {
			return fov;
		}

		void setFov(float fov) {
			this->fov = fov;
		}

		const string& getLabel() {
			return label;
		}

		void setLabel(const string &label) {
			this->label = label;
		}

		float getMovementSpeed() {
			return movementSpeed;
		}

		void setMovementSpeed(float movementSpeed) {
			this->movementSpeed = movementSpeed;
		}

		float getPitch() {
			return pitch;
		}

		void setPitch(float pitch) {
			this->pitch = pitch;
		}

		float getSensitivity() {
			return sensitivity;
		}

		void setSensitivity(float sensitivity) {
			this->sensitivity = sensitivity;
		}

		float getYaw() {
			return yaw;
		}

		void setYaw(float yaw) {
			this->yaw = yaw;
		}
	private:
		static Camera* selectedCamera;
};

#endif