#pragma once

#include "importBase.h"

namespace mesh_import {

	class ObjMeshImporter : public IMeshImporter
	{
	public:
		virtual bool fromFile(const std::string& filepath, elements::Mesh* pMesh) override;

	};
}
