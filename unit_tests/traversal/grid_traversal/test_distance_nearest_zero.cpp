#include <vector>
#include <gtest/gtest.h>
#include "traversal/grid_traversal/distance_nearest_zero.hpp"



TEST(NearestDistanceTo0,FireCodeCase) {
    std::vector<std::vector<int>> input={{0,0,0},{0,1,0},{1,1,1}};
    std::vector<std::vector<int>> expected={{0,0,0},{0,1,0},{1,2,1}};
    std::vector<std::vector<int>> actual=nearestDistanceTo0(input);
    EXPECT_EQ(expected,actual);

}

TEST(NearestDistanceTo0,OneElementInput) {
    std::vector<std::vector<int>> input={{0}};
    std::vector<std::vector<int>> expected={{0}};
    std::vector<std::vector<int>> actual=nearestDistanceTo0(input);

}