#include <gtest/gtest.h>
#include "traversal/grid_traversal/nearest_exit_from_entrance.hpp"
#include <vector>

// LeetCode example 1: exit one step directly above entrance
TEST(NearestExitFromEntrance, LeetCodeExample1) {
    std::vector<std::vector<char>> maze = {
        {'+', '+', '.', '+'},
        {'.', '.', '.', '+'},
        {'+', '+', '+', '.'}
    };
    EXPECT_EQ(nearestExit(maze, {1, 2}), 1);
}

// LeetCode example 2: exit two steps to the right along the only open row
TEST(NearestExitFromEntrance, LeetCodeExample2) {
    std::vector<std::vector<char>> maze = {
        {'+', '+', '+'},
        {'.', '.', '.'},
        {'+', '+', '+'}
    };
    EXPECT_EQ(nearestExit(maze, {1, 0}), 2);
}

// LeetCode example 3: entrance on border but the only other border cell is a wall
TEST(NearestExitFromEntrance, LeetCodeExample3) {
    std::vector<std::vector<char>> maze = {
        {'.', '+'}
    };
    EXPECT_EQ(nearestExit(maze, {0, 0}), -1);
}

// Entrance is completely surrounded by walls — no path exists
TEST(NearestExitFromEntrance, EntranceSurroundedByWalls) {
    std::vector<std::vector<char>> maze = {
        {'+', '+', '+', '+', '+'},
        {'+', '.', '+', '.', '+'},
        {'+', '+', '.', '+', '+'},
        {'+', '.', '+', '.', '+'},
        {'+', '+', '+', '+', '+'}
    };
    EXPECT_EQ(nearestExit(maze, {2, 2}), -1);
}

// Single open row — every cell is a border cell (row 0 == last row), so nearest exit is 1 step
TEST(NearestExitFromEntrance, SingleRowEntranceInMiddle) {
    std::vector<std::vector<char>> maze = {
        {'.', '.', '.', '.', '.'}
    };
    EXPECT_EQ(nearestExit(maze, {0, 2}), 1);
}

// Single open column — every cell is a border cell (col 0 == last col), so nearest exit is 1 step
TEST(NearestExitFromEntrance, SingleColumnEntranceInMiddle) {
    std::vector<std::vector<char>> maze = {
        {'.'},
        {'.'},
        {'.'},
        {'.'},
        {'.'}
    };
    EXPECT_EQ(nearestExit(maze, {2, 0}), 1);
}

// Entrance is at a corner — nearest exit is one step away along the border
TEST(NearestExitFromEntrance, EntranceAtCornerExitOneStep) {
    std::vector<std::vector<char>> maze = {
        {'.', '.', '+'},
        {'+', '.', '+'},
        {'+', '+', '+'}
    };
    EXPECT_EQ(nearestExit(maze, {0, 0}), 1);
}

// Multiple exits reachable — BFS must return the distance to the closest one
TEST(NearestExitFromEntrance, MultipleExitsPickShortest) {
    std::vector<std::vector<char>> maze = {
        {'+', '.', '+', '+', '+'},
        {'+', '.', '.', '.', '+'},
        {'+', '+', '+', '.', '+'},
        {'+', '+', '+', '.', '.'}
    };
    // From [1,1]: up to [0,1] = 1 step; right path leads to [3,4] = 5 steps
    EXPECT_EQ(nearestExit(maze, {1, 1}), 1);
}

// Winding maze where the only path requires going around obstacles
TEST(NearestExitFromEntrance, WindingPathToExit) {
    std::vector<std::vector<char>> maze = {
        {'+', '+', '+', '+', '+'},
        {'.', '.', '+', '.', '+'},
        {'+', '.', '+', '.', '+'},
        {'+', '.', '.', '.', '+'},
        {'+', '+', '+', '+', '.'}
    };
    // Entrance at [1,0] (left border — is itself a border cell but not an exit).
    // Path: [1,0]->[1,1]->[2,1]->[3,1]->[3,2]->[3,3]->[2,3]->[1,3] = 7 steps to [1,3] (not border)
    // Only true exit reachable: [4,4] border cell.
    // [1,0]->[1,1]->[2,1]->[3,1]->[3,2]->[3,3]->[2,3]->[1,3] not border
    // Continue: [4,4] needs path from [3,3] but [4,3]='+'. 
    // Recheck: [3,3] neighbors: up=[2,3]('.'), left=[3,2]('.'), down=[4,3]('+'), right=[3,4]('+')
    // [1,3] is border (col 3, not last col) — not border. [1,4]='+'. 
    // Actually [1,3] border? row=1, col=3, rows=5,cols=5 -> not border. 
    // No reachable border '.': return -1.
    EXPECT_EQ(nearestExit(maze, {1, 0}), -1);
}

// Entrance on the border — the entrance itself must NOT count as exit
TEST(NearestExitFromEntrance, EntranceOnBorderDoesNotCount) {
    std::vector<std::vector<char>> maze = {
        {'.', '.', '.'},
        {'.', '+', '.'},
        {'.', '.', '.'}
    };
    // Entrance at [0,0] (border). Adjacent border exits: [0,1] and [1,0] each 1 step away.
    EXPECT_EQ(nearestExit(maze, {0, 0}), 1);
}

// 1x1 maze — no exit can ever exist (entrance fills the whole maze)
TEST(NearestExitFromEntrance, SingleCellMaze) {
    std::vector<std::vector<char>> maze = {
        {'.'}
    };
    EXPECT_EQ(nearestExit(maze, {0, 0}), -1);
}
