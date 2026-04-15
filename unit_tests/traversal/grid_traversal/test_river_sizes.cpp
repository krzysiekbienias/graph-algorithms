#include <gtest/gtest.h>
#include "graph.hpp"
#include "traversal/grid_traversal/river_sizes.hpp"

TEST(RiverSizes, BasicCase) {
    std::vector<std::vector<int>> testInput{
            {1, 0, 0, 1, 0},
            {1, 0, 1, 0, 0},
            {0, 0, 1, 0, 1},
            {1, 0, 1, 0, 1},
            {1, 0, 1, 1, 0},
          };
    std::vector<int> expected{1, 2, 2, 2, 5};

    std::vector<int> actual=riverSizes(testInput);




}