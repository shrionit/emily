#include "SceneComponent.h"

void SceneComponent::render(){
    Begin(label.c_str());
    {
        if(ImGui::TreeNode("Scene")){
            if(ImGui::TreeNode("Entities")){
                map<string, Entity*> entities = getCurrentScene()->getEntities();
                map<string, Entity*>::iterator itr;
                Entity* selectedEntity = getCurrentScene()->getSelectedEntity();
                for(itr = entities.begin(); itr != entities.end(); ++itr){
                    if (ImGui::Selectable(itr->first.c_str(), itr->first == selectedEntity->getID())) {
                        selectedEntity = itr->second;
                    }
                    if(itr->first == getCurrentScene()->getSelectedEntity()->getID()){
                        ImGui::TextColored(ImVec4(1,1,1,1), itr->second->getLabel().c_str());
                    }else{
                        ImGui::TextColored(ImVec4(0.5, 0.5, 0.5, 1.0), itr->second->getLabel().c_str());
                    }
                }
                GUI::emitter.emit(selectedEntity);
                getCurrentScene()->setSelectedEntity(selectedEntity);
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Trees")) {
                if (ImGui::TreeNode("Basic trees")) {
                    for (int i = 0; i < 5; i++) {
                        // Use SetNextItemOpen() so set the default state of a node to be open. We could
                        // also use TreeNodeEx() with the ImGuiTreeNodeFlags_DefaultOpen flag to achieve the same thing!
                        if (i == 0)
                            ImGui::SetNextItemOpen(true, ImGuiCond_Once);
                        if (ImGui::TreeNode((void*)(intptr_t)i, "Child %d", i)) {
                            ImGui::Text("blah blah");
                            ImGui::SameLine();
                            if (ImGui::SmallButton("button")) {}
                            ImGui::TreePop();
                        }
                    }
                    ImGui::TreePop();
                }

                if (ImGui::TreeNode("Advanced, with Selectable nodes")) {
                    static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
                    static bool align_label_with_current_x_position = false;
                    static bool test_drag_and_drop = false;
                    ImGui::CheckboxFlags("ImGuiTreeNodeFlags_OpenOnArrow",       &base_flags, ImGuiTreeNodeFlags_OpenOnArrow);
                    ImGui::CheckboxFlags("ImGuiTreeNodeFlags_OpenOnDoubleClick", &base_flags, ImGuiTreeNodeFlags_OpenOnDoubleClick);
                    ImGui::CheckboxFlags("ImGuiTreeNodeFlags_SpanAvailWidth",    &base_flags, ImGuiTreeNodeFlags_SpanAvailWidth); ImGui::SameLine();
                    ImGui::CheckboxFlags("ImGuiTreeNodeFlags_SpanFullWidth",     &base_flags, ImGuiTreeNodeFlags_SpanFullWidth);
                    ImGui::Checkbox("Align label with current X position", &align_label_with_current_x_position);
                    ImGui::Checkbox("Test tree node as drag source", &test_drag_and_drop);
                    ImGui::Text("Hello!");
                    if (align_label_with_current_x_position)
                        ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());

                    // 'selection_mask' is dumb representation of what may be user-side selection state.
                    //  You may retain selection state inside or outside your objects in whatever format you see fit.
                    // 'node_clicked' is temporary storage of what node we have clicked to process selection at the end
                    /// of the loop. May be a pointer to your own node type, etc.
                    static int selection_mask = (1 << 2);
                    int node_clicked = -1;
                    for (int i = 0; i < 6; i++) {
                        // Disable the default "open on single-click behavior" + set Selected flag according to our selection.
                        // To alter selection we use IsItemClicked() && !IsItemToggledOpen(), so clicking on an arrow doesn't alter selection.
                        ImGuiTreeNodeFlags node_flags = base_flags;
                        const bool is_selected = (selection_mask & (1 << i)) != 0;
                        if (is_selected)
                            node_flags |= ImGuiTreeNodeFlags_Selected;
                        if (i < 3) {
                            // Items 0..2 are Tree Node
                            bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "Selectable Node %d", i);
                            if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
                                node_clicked = i;
                            if (test_drag_and_drop && ImGui::BeginDragDropSource()) {
                                ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
                                ImGui::Text("This is a drag and drop source");
                                ImGui::EndDragDropSource();
                            }
                            if (node_open) {
                                ImGui::BulletText("Blah blah\nBlah Blah");
                                ImGui::TreePop();
                            }
                        } else {
                            // Items 3..5 are Tree Leaves
                            // The only reason we use TreeNode at all is to allow selection of the leaf. Otherwise we can
                            // use BulletText() or advance the cursor by GetTreeNodeToLabelSpacing() and call Text().
                            node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen; // ImGuiTreeNodeFlags_Bullet
                            ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "Selectable Leaf %d", i);
                            if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
                                node_clicked = i;
                            if (test_drag_and_drop && ImGui::BeginDragDropSource()) {
                                ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
                                ImGui::Text("This is a drag and drop source");
                                ImGui::EndDragDropSource();
                            }
                        }
                    }
                    if (node_clicked != -1) {
                        // Update selection state
                        // (process outside of tree loop to avoid visual inconsistencies during the clicking frame)
                        if (ImGui::GetIO().KeyCtrl)
                            selection_mask ^= (1 << node_clicked);          // CTRL+click to toggle
                        else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, may want to preserve selection when clicking on item that is part of the selection
                            selection_mask = (1 << node_clicked);           // Click to single-select
                    }
                    if (align_label_with_current_x_position)
                        ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());
                    ImGui::TreePop();
                }
            ImGui::TreePop();
        }
    }
    End();
}