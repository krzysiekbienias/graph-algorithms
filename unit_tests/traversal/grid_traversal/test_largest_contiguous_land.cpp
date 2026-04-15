#include <gtest/gtest.h>
#include <traversal/grid_traversal/largest_contiguous_land.hpp>


TEST(MaxAreaOfIsland,BaseCase) {
    std::vector<std::vector<int>> world= {
  {0,0,1,0,0,0,0,1,0,0,0,0,0},
  {0,0,0,0,0,0,0,1,1,1,0,0,0},
  {0,1,1,0,1,0,0,0,0,0,0,0,0},
  {0,1,0,0,1,1,0,0,1,0,1,0,0},
  {0,1,0,0,1,1,0,0,1,1,1,0,0},
  {0,0,0,0,0,0,0,0,0,0,1,0,0},
  {0,0,0,0,0,0,0,1,1,1,0,0,0},
  {0,0,0,0,0,0,0,1,1,0,0,0,0}};

    int expected=maxAreaOfIsland(world);
    EXPECT_EQ(expected,6);
}