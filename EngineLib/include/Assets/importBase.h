#pragma once
#include "EngineCore.h"

#include "Scene/Mesh.h"
#include "Platform/Logger.h"

extern ENGINE_API Debug gLog;

namespace mesh_import {

	struct IMeshImporter
	{
    virtual bool fromFile(const std::string& filepath, elements::Mesh* pMesh) = 0;
	};
}