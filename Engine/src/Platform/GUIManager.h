/*#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include "pch.h"
#include "window.h"

#include "Scene/ControlPanel.h"
#include "Scene/SimulationPanels.h"
#include "Scene/DebugPanel.h"
#include "Scene/Styles.h"



#include "Render/SimulationManager.h"

using namespace window;

class GUIManager
{
public:
	explicit GUIManager(GLWindow* _window);

	void InitResources();
	void BeginFrame();
	void EndFrame();
	void DrawPanel();

private:
	ImVec2 winSize;
	ImVec2 padding;
	float debugHeight = 0.0f;
	float ctrlPanelWidth = 0.0f;

	void ContainerPanel();
	window::GLWindow* _window;

	ControlPanel ctrlPanel;
	SimulationPanels simPanel;
	DebugPanel debug;
	StyleModes styles;
	std::unique_ptr<SimulationManager> simulation;
};

#endif*/