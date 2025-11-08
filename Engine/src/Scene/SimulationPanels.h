/*#ifndef SIMULATION_PANELS_H
#define SIMULATION_PANELS_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "../Render/SimulationManager.h"

namespace gui {
	class SimulationPanels
	{
	public:
		void Render(ImVec2 winSize, ImVec2 padding, float debugHeight, float ctrlPanelWidth, SimulationManager* sim);

	private:
		void MainPanel(SimulationManager* sim);
		void SecondaryPanels();
	};
}

#endif */