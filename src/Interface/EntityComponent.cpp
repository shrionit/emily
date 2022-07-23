#include "EntityComponent.h"
std::map<int, GLuint> FillMode::modes;
Entity* EntityComponent::selectedEntity = nullptr;
vector<FillMode> EntityComponent::fillModes;

void EntityComponent::render(){
    Begin(label.c_str());
    Checkbox("Show", &visible);
    GUI::BeginGroupPanel("Draw Mode", ImVec2(-1.0f, 0.0f));
    {
        for(auto e : fillModes){
            RadioButton(e.name, &drawModeNumber, e.value);
            SameLine();
        }
    }
    GUI::EndGroupPanel();
    GUI::BeginGroupPanel("Entity Position", ImVec2(-1.0f, 0.0f));
    {
        BeginColumns("EntityPosition", 2, 0);
        IMGUI_LEFT_LABEL(InputFloat("##Position X", &position[0], 0.001f, 0.05f, "%.4f", 0), "Position X");
        IMGUI_LEFT_LABEL(InputFloat("##Position Y", &position[1], 0.001f, 0.05f, "%.4f", 0), "Position Y");
        IMGUI_LEFT_LABEL(InputFloat("##Position Z", &position[2], 0.001f, 0.05f, "%.4f", 0), "Position Z");
        EndColumns();
    }
    GUI::EndGroupPanel();
    GUI::BeginGroupPanel("Entity Rotation", ImVec2(-1.0f, 0.0f));
    {
        BeginColumns("EntityRotation", 2, 0);
        IMGUI_LEFT_LABEL(InputFloat("##Rotation X", &rotation[0], 0.001f, 0.05f, "%.4f", 0), "Rotation X");
        IMGUI_LEFT_LABEL(InputFloat("##Rotation Y", &rotation[1], 0.001f, 0.05f, "%.4f", 0), "Rotation Y");
        IMGUI_LEFT_LABEL(InputFloat("##Rotation Z", &rotation[2], 0.001f, 0.05f, "%.4f", 0), "Rotation Z");
        EndColumns();
    }
    GUI::EndGroupPanel();
    GUI::BeginGroupPanel("Entity Scale", ImVec2(-1.0f, 0.0f));
    {
        BeginColumns("EntityScale", 2, 0);
        IMGUI_LEFT_LABEL(InputFloat("##Scale X", &scale[0], 0.001f, 0.05f, "%.4f", 0), "Scale X");
        IMGUI_LEFT_LABEL(InputFloat("##Scale Y", &scale[1], 0.001f, 0.05f, "%.4f", 0), "Scale Y");
        IMGUI_LEFT_LABEL(InputFloat("##Scale Z", &scale[2], 0.001f, 0.05f, "%.4f", 0), "Scale Z");
        EndColumns();
    }
    GUI::EndGroupPanel();
    End();
    selectedEntity->setPosition(getPosition());
    selectedEntity->setRotation(getRotation());
    selectedEntity->setScale(getScale());
    selectedEntity->setVisible(isVisible());
    selectedEntity->setDrawMode(getDrawMode());
}