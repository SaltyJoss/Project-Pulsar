#include "gtest/gtest.h"
#include "import/obj_importer.h"

TEST(ImportTest, SimpleObjLoads) {
    ObjModel m = ImportObj("cube.obj");

    EXPECT_GT(m.vertices.size(), 0);
    EXPECT_GT(m.indices.size(), 0);
}