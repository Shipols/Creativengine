#include "ObjectsWindow.h"

ObjectsWindow::ObjectsWindow()
{
	ImGui::Begin("Objects");

	if (ImGui::TreeNodeEx("Scene")) {

		ImGui::TreePop();

	}

	ImGui::End();
}

ObjectsWindow::~ObjectsWindow()
{

}
