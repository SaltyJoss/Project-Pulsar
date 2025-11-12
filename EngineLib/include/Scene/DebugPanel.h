#pragma once
#include "EngineCore.h"

#include "imgui.h"
#include "SceneView.h"
#include "Camera.h"
#include "Platform/Logger.h"

extern ENGINE_API Debug gLog;

namespace gui {
	class ENGINE_API DebugPanel {
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