#pragma once
#include "EngineCore.h"

#include "importBase.h"
#include "Platform/Logger.h"

extern ENGINE_API Debug gLog;

namespace mesh_import {

	class ENGINE_API ObjMeshImporter : public IMeshImporter
	{
	public:
		virtual bool fromFile(const std::string& filepath, elements::Mesh* pMesh) override;

	};
}
