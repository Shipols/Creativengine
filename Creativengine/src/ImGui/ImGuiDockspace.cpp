#include "ImGuiDockspace.h"

#include "Logger/LoggerFunctions.h"

#include "ImGui/docking/imgui.h"

namespace Creativengine {

	void ShowImGuiDockSpace(GLFWwindow* window)
	{
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace", (bool*)true, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("Dockspace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{

				if (ImGui::MenuItem("Save As..."))
				{

					// Save as code here.
				}

				if (ImGui::MenuItem("Open"))
				{

				}

				ImGui::Separator();

				if (ImGui::MenuItem("Quit"))
				{
					glfwDestroyWindow(window);
					PrintInfo("Creativengine was closed.You can now safely close this window.");
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Object"))
			{
				if (ImGui::BeginMenu("Add Object")) {

					if (ImGui::MenuItem("Empty Object")) {}
					ImGui::Separator();
					if (ImGui::MenuItem("Square")) {}
					if (ImGui::MenuItem("Empty Object with Texture")) {}

					ImGui::EndMenu();
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Game"))
			{
				if (ImGui::MenuItem("Play")) {}
				if (ImGui::MenuItem("Pause"), (bool*)false, (bool*) false) {}

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::End();
	}

}