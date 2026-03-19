#include <gtest/gtest.h>

#include "traversal/grid_traversal/nb_of_islands.hpp"


TEST(NbOfIsland,SimpleCase) {
    std::vector<std::vector<int>> world={
        {1,1,0,0,0},
        {1,1,0,0,0},
        {0,0,1,0,0},
        {0,0,0,1,1},
    };
    int actual= countIslands(world);
    EXPECT_EQ(actual,3);
}

TEST(NbOfIsland,SingleLand) {
    std::vector<std::vector<int>> world={
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,1,1,1},

    };
    int actual= countIslands(world);
    EXPECT_EQ(actual,1);
}