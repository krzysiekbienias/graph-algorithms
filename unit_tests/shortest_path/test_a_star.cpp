#include <gtest/gtest.h>
#include <vector>
#include "shortest_path/a_star.hpp"

TEST(AStarAlgorithm, ProblemStatementExample) {
    auto startRow = 0;
    auto startCol = 1;
    auto endRow = 4;
    auto endCol = 3;
    std::vector<std::vector<int>> graph = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
        {1, 0, 1, 1, 1},
        {0, 0, 0, 0, 0},
    };
    std::vector<std::vector<int>> expected = {
        {0, 1}, {0, 0}, {1, 0}, {2, 0}, {2, 1}, {3, 1}, {4, 1}, {4, 2}, {4, 3}};

    std::vector<std::vector<int>> actual =
        aStarAlgorithm(startRow, startCol, endRow, endCol, graph);

    EXPECT_EQ(expected, actual);
}
