#pragma once

#include "imgui.h"
#include "SceneView.h"
#include "Camera.h"

extern Debug gLog; // Global Variable for debugging and logs

namespace gui {
	class DebugPanel {
	public:
		void render();
		void addLog(const std::string& msg, bool error = false);

	private:
		struct LogEntry { std::string text; bool isError; };
		std::vector<LogEntry> entries;
		bool autoScroll = true;

		void renderLog();
		void renderErrors();
		ImVec4 getColour(bool error) const;
	};
}