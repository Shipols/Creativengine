#include "ImGuiStyle.h"

void SetImGuiStyle()
{

	ImVec4* colors = ImGui::GetStyle().Colors;

	ImGui::GetIO().Fonts->AddFontFromFileTTF("res/fonts/OpenSans.ttf", 16);
	
	ImGui::GetStyle().FrameBorderSize = 1.0f;
	ImGui::GetStyle().ScrollbarRounding = 0.0f;
	ImGui::GetStyle().TabRounding = 0.0f;

	colors[ImGuiCol_FrameBg] = ImVec4(0.45f, 0.45f, 0.45f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.85f, 0.85f, 0.85f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.87f, 0.87f, 0.87f, 0.67f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.72f, 0.72f, 0.72f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.74f, 0.74f, 0.74f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.59f, 0.59f, 0.59f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.68f, 0.68f, 0.68f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.48f, 0.48f, 0.48f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.51f, 0.51f, 0.51f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.46f, 0.46f, 0.46f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.77f, 0.77f, 0.77f, 0.20f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.65f, 0.65f, 0.65f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.61f, 0.61f, 0.61f, 0.95f);
	colors[ImGuiCol_Tab] = ImVec4(0.52f, 0.52f, 0.52f, 0.86f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.76f, 0.76f, 0.76f, 0.80f);
	colors[ImGuiCol_TabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.13f, 0.13f, 0.13f, 0.97f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.45f, 0.45f, 0.45f, 1.00f);
	colors[ImGuiCol_DockingPreview] = ImVec4(0.60f, 0.60f, 0.60f, 0.70f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.76f, 0.76f, 0.76f, 0.35f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.55f, 0.55f, 0.55f, 1.00f);
}

