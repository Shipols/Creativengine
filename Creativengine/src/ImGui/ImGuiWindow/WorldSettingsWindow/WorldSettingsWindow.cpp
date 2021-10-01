#include "WorldSettingsWindow.h"

#include <LibraryIncludes.h>

namespace Creativengine {

	WorldSettingsWindow::WorldSettingsWindow(ImVec4 skyColor)
		: m_skyColor(skyColor)
	{
	}

	WorldSettingsWindow::~WorldSettingsWindow()
	{

	}

	void WorldSettingsWindow::Render()
	{
		ImGui::Begin("World Settings");

		ImGui::ColorEdit3("Sky Color", (float*)&m_skyColor);

		ImGui::End();
		
		glClearColor(m_skyColor.x * m_skyColor.w, m_skyColor.y * m_skyColor.w, m_skyColor.z * m_skyColor.w, m_skyColor.w);
	}

}