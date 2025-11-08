#pragma once

#include "pch.h"

#include "RenderBase.h"
#include "Scene/VertexHolder.h"
#include "Scene/Element.h"

#include "Scene/Face.h"

namespace render {
	class Cubemap {
	public:
		Cubemap(const std::array<std::string, 6>& faces);
		~Cubemap();

		void bind(unsigned int unit = 0) const;
		unsigned int ID() const;

	private:
		unsigned int _cubemapTexture;
		bool _isLoaded;
	};
}