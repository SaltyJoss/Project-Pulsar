#pragma once
#include "pch.h"
#include "Scene/Mesh.h"

namespace mesh_import {

	struct IMeshImporter
	{
    virtual bool fromFile(const std::string& filepath, elements::Mesh* pMesh) = 0;
	};
}