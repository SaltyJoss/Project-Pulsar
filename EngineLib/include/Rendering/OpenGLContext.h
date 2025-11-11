#pragma once

#include "EngineCore.h"

#include "RenderBase.h"
#include "Scene/Styles.h"

extern Debug gLog; // Global Variable for debugging and logs

namespace render {
	class OpenGLContext : public RenderContext {
	public:
		bool init(window::IWindow* window) override;
		void preRender() override;
		void postRender() override;
		void end() override;
	};
}