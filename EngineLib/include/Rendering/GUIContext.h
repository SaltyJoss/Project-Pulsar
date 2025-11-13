#pragma once
#include "EngineCore.h"

#include "RenderBase.h"
#include "Scene/Styles.h"
#include "Platform/Logger.h"

extern ENGINE_API Debug gLog;

namespace render {
	class ENGINE_API GUIContext : public RenderContext {
	public:
		bool init(window::IWindow* win) override;
		void preRender() override;
		void postRender() override;
		void end() override;

	private:
		std::unique_ptr<gui::Styles> _style;
	};
}