#pragma once
#include "ch.h"
#include "Elements/Mesh.h"

namespace mesh_import {

	struct IMeshImporter
	{
    virtual bool fromFile(const std::string& filepath, elements::Mesh* pMesh) = 0;
	};
}