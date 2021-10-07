#include "ObjectTreeView.h"

#include "Logger/LoggerFunctions.h"

ObjectTreeView::ObjectTreeView(const char* name)
{
	if (ImGui::TreeNodeEx(name))
	{
		if (ImGui::IsItemClicked(0))
		{

		}

		ImGui::TreePop();
	}
}

ObjectTreeView::~ObjectTreeView()
{

}
