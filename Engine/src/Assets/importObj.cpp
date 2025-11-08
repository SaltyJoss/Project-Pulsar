#include "pch.h"
#include "importObj.h"
#include "Scene/VertexHolder.h"
#include "Platform/str_utils.h"

namespace mesh_import
{
  bool ObjMeshImporter::fromFile(const std::string& filepath, elements::Mesh* pMesh)
  {
    std::ifstream in(filepath, std::ios::in);
    if (!in) {
      LOG_ERROR("Failed to open OBJ file: %s", filepath.c_str());
      return false;
    }

    LOG_INFO("Importing OBJ file: %s", filepath.c_str());

    std::vector<glm::vec3> t_vert;
    std::string s_line;

    while (std::getline(in, s_line)) {
      std::istringstream ss_line(s_line);
      std::string id;
      ss_line >> id;

      if (id == "v") {
        glm::vec3 v;

        ss_line >> v.x >> v.y >> v.z;

        t_vert.push_back(v);
      }

      // Faces
      else if (id == "f") {
        // TASK1: Add quads
        // TASK2: read indices for normals and UVs
        // TASK3: Optimize data structure to cache indices (map) -> IMPORTANT
        std::string v1, v2, v3;
        ss_line >> v1 >> v2 >> v3;

        uint32_t vert_idx[3];
        vert_idx[0] = utils::tokenize(v1, '/').at(0);
        vert_idx[1] = utils::tokenize(v2, '/').at(0);
        vert_idx[2] = utils::tokenize(v3, '/').at(0);

        pMesh->addVertexIndex(vert_idx[0] - 1);
        pMesh->addVertexIndex(vert_idx[1] - 1);
        pMesh->addVertexIndex(vert_idx[2] - 1);

      }
    }

    // Now use the indices to create the concrete vertices for the mesh
    for (auto v_idx : pMesh->getVertexIndices()) {
        if (v_idx < t_vert.size()) {
            glm::vec3 vertex = t_vert[v_idx];
            elements::VertexHolder vh(vertex, glm::vec3(0.0f, 0.0f, 0.0f)); // default normal
            pMesh->addVertex(vh);  // now types match
        }
        else {
            LOG_WARN_ONCE("Vertex index out of range: %u", v_idx);
        }
    } 

    LOG_INFO("OBJ import completed: %s", filepath.c_str());
    return true;
  }
}