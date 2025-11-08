#pragma once

#include "pch.h"

namespace gui {
	class FpsCounter {
	public:
		void update() {
			double now = glfwGetTime();
			double dt = now - last;

			last = now;
			frames++;
			accum += dt;
			if (accum >= 1.0) {
				fps = frames / accum;
				frames = 0;
				accum = 0.0;
			}
		}

		double getFPS() const { return fps; }

	private:
		bool init = false;
		double last = glfwGetTime();
		double accum = 0.0;
		int frames = 0;
		double fps = 0.0;
	};
}