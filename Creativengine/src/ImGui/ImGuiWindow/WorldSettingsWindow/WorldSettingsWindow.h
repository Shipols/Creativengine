#pragma once

#include "ImGui\docking\imgui.h"

namespace Creativengine {

	class WorldSettingsWindow
	{
	public:

		WorldSettingsWindow(ImVec4 skyColor);
		~WorldSettingsWindow();

		void Render();
	
	private:
	};

}