#include "ObjectsWindow.h"
#include "ObjectTreeView/ObjectTreeView.h"

namespace Creativengine {

	ObjectsWindow::ObjectsWindow()
	{
	}

	ObjectsWindow::~ObjectsWindow()
	{

	}

	void ObjectsWindow::Render()
	{
		ImGui::Begin("Objects");

		if (ImGui::TreeNodeEx("Scene"))
		{
			ImGui::TreePop();

		}

		ImGui::End();
	}

}