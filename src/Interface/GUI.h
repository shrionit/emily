#ifndef GUI_H
#define GUI_H
#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_LEFT_LABEL(func, label) TextUnformatted(label); NextColumn(); SetNextItemWidth(-1); func; NextColumn();
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imstb_rectpack.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <Event/EventEmitter.h>
#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include <map>

using namespace ImGui;
static ImVector<ImRect> s_GroupPanelLabelStack;
class GUI {
	public:
		static EMILY::EventEmitter emitter;
		static GLFWwindow* window;
		GUI(){}
		void registerComponent(GUI* c){
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
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
			io.Fonts->AddFontFromFileTTF("C:\\fonts\\Caskaydia Cove Nerd Font Complete.ttf", 16.0f);
			StyleColorsDark();
			ImGui_ImplGlfw_InitForOpenGL(win, true);
			ImGui_ImplOpenGL3_Init("#version 400");
		}

		static void closeGUI(){
			ImGui_ImplGlfw_Shutdown();
			ImGui_ImplOpenGL3_Shutdown();
			DestroyContext();
		}
		static void renderGUI();
		static void BeginGroupPanel(const char* name, const ImVec2& size = ImVec2(-1.0f, -1.0f)) {
			BeginGroup();

			auto cursorPos = GetCursorScreenPos();
			auto itemSpacing = GetStyle().ItemSpacing;
			PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
			PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

			auto frameHeight = GetFrameHeight();
			BeginGroup();

			ImVec2 effectiveSize = size;
			if (size.x < 0.0f)
				effectiveSize.x = GetContentRegionAvail().x;
			else
				effectiveSize.x = size.x;
			Dummy(ImVec2(effectiveSize.x, 0.0f));

			Dummy(ImVec2(frameHeight * 0.5f, 0.0f));
			SameLine(0.0f, 0.0f);
			BeginGroup();
			Dummy(ImVec2(frameHeight * 0.5f, 0.0f));
			SameLine(0.0f, 0.0f);
			TextUnformatted(name);
			auto labelMin = GetItemRectMin();
			auto labelMax = GetItemRectMax();
			SameLine(0.0f, 0.0f);
			Dummy(ImVec2(0.0, frameHeight + itemSpacing.y));
			BeginGroup();

			//GetWindowDrawList()->AddRect(labelMin, labelMax, IM_COL32(255, 0, 255, 255));

			PopStyleVar(2);

			#if IMGUI_VERSION_NUM >= 17301
				GetCurrentWindow()->ContentRegionRect.Max.x -= frameHeight * 0.5f;
				GetCurrentWindow()->WorkRect.Max.x          -= frameHeight * 0.5f;
				GetCurrentWindow()->InnerRect.Max.x         -= frameHeight * 0.5f;
			#else
				GetCurrentWindow()->ContentsRegionRect.Max.x -= frameHeight * 0.5f;
			#endif
				GetCurrentWindow()->Size.x                   -= frameHeight;

				auto itemWidth = CalcItemWidth();
				PushItemWidth(ImMax(0.0f, itemWidth - frameHeight));

			s_GroupPanelLabelStack.push_back(ImRect(labelMin, labelMax));
		}

		static void EndGroupPanel() {
			PopItemWidth();

			    auto itemSpacing = GetStyle().ItemSpacing;

			    PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
			    PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

			    auto frameHeight = GetFrameHeight();

			    EndGroup();

			    //GetWindowDrawList()->AddRectFilled(GetItemRectMin(), GetItemRectMax(), IM_COL32(0, 255, 0, 64), 4.0f);

			    EndGroup();

			    SameLine(0.0f, 0.0f);
			    Dummy(ImVec2(frameHeight * 0.5f, 0.0f));
			    Dummy(ImVec2(0.0, frameHeight - frameHeight * 0.5f - itemSpacing.y));

			    EndGroup();

			    auto itemMin = GetItemRectMin();
			    auto itemMax = GetItemRectMax();
			    //GetWindowDrawList()->AddRectFilled(itemMin, itemMax, IM_COL32(255, 0, 0, 64), 4.0f);

			    auto labelRect = s_GroupPanelLabelStack.back();
			    s_GroupPanelLabelStack.pop_back();

			    ImVec2 halfFrame = ImVec2(frameHeight * 0.25f, frameHeight) * 0.5f;
			    ImRect frameRect = ImRect(itemMin + halfFrame, itemMax - ImVec2(halfFrame.x, 0.0f));
			    labelRect.Min.x -= itemSpacing.x;
			    labelRect.Max.x += itemSpacing.x;
			    for (int i = 0; i < 4; ++i)
			    {
			        switch (i)
			        {
			            // left half-plane
			            case 0: PushClipRect(ImVec2(-FLT_MAX, -FLT_MAX), ImVec2(labelRect.Min.x, FLT_MAX), true); break;
			            // right half-plane
			            case 1: PushClipRect(ImVec2(labelRect.Max.x, -FLT_MAX), ImVec2(FLT_MAX, FLT_MAX), true); break;
			            // top
			            case 2: PushClipRect(ImVec2(labelRect.Min.x, -FLT_MAX), ImVec2(labelRect.Max.x, labelRect.Min.y), true); break;
			            // bottom
			            case 3: PushClipRect(ImVec2(labelRect.Min.x, labelRect.Max.y), ImVec2(labelRect.Max.x, FLT_MAX), true); break;
			        }

			        GetWindowDrawList()->AddRect(
			            frameRect.Min, frameRect.Max,
			            ImColor(GetStyleColorVec4(ImGuiCol_Border)),
			            halfFrame.x);

			        PopClipRect();
			    }

			    PopStyleVar(2);

			#if IMGUI_VERSION_NUM >= 17301
			    GetCurrentWindow()->ContentRegionRect.Max.x += frameHeight * 0.5f;
			    GetCurrentWindow()->WorkRect.Max.x          += frameHeight * 0.5f;
			    GetCurrentWindow()->InnerRect.Max.x         += frameHeight * 0.5f;
			#else
			    GetCurrentWindow()->ContentsRegionRect.Max.x += frameHeight * 0.5f;
			#endif
			    GetCurrentWindow()->Size.x                   += frameHeight;

			    Dummy(ImVec2(0.0f, 0.0f));

			    EndGroup();
		}
	private:
		static std::vector<GUI*> components;
};

#endif
