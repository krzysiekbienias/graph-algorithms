#include <gtest/gtest.h>
#include "traversal/grid_traversal/fastest_route_to_food.hpp"
#include <vector>

TEST(GetFoodTest, FoodNextToStart) {
    std::vector<std::vector<char>> grid = {
        {'*', '#', 'O', 'X', '#', 'O'}
    };

    EXPECT_EQ(getFood(grid), 1);
}

TEST(GetFoodTest, NoFoodReachableInOpenGrid) {
    std::vector<std::vector<char>> grid = {
        {'*', 'O', 'O'},
        {'O', 'X', 'O'},
        {'O', 'O', 'O'}
    };

    EXPECT_EQ(getFood(grid), -1);
}

TEST(GetFoodTest, VerticalBlockedPath) {
    std::vector<std::vector<char>> grid = {
        {'*'},
        {'X'},
        {'O'},
        {'#'},
        {'O'}
    };

    EXPECT_EQ(getFood(grid), -1);
}

TEST(GetFoodTest, WindingPathToFood) {
    std::vector<std::vector<char>> grid = {
        {'X', '*', 'X', 'O', 'X'},
        {'O', 'O', 'O', 'O', 'O'},
        {'X', 'O', 'X', '#', 'X'},
        {'X', 'O', 'O', 'O', 'X'}
    };

    EXPECT_EQ(getFood(grid), 4);
}

TEST(GetFoodTest, MultipleFoodsChooseShortestPath) {
    std::vector<std::vector<char>> grid = {
        {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
        {'X', '*', 'O', 'X', 'O', '#', 'O', 'X'},
        {'X', 'O', 'O', 'X', 'O', 'O', 'X', 'X'},
        {'X', 'O', 'O', 'O', 'O', '#', 'O', 'X'},
        {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'}
    };

    EXPECT_EQ(getFood(grid), 6);
}

TEST(GetFoodTest, ClassicExample) {
    std::vector<std::vector<char>> grid = {
        {'X', 'X', 'X', 'X', 'X', 'X'},
        {'X', '*', 'O', 'O', 'O', 'X'},
        {'X', 'O', 'O', '#', 'O', 'X'},
        {'X', 'X', 'X', 'X', 'X', 'X'}
    };

    EXPECT_EQ(getFood(grid), 3);
}

TEST(GetFoodTest, FoodBlockedByWalls) {
    std::vector<std::vector<char>> grid = {
        {'X', 'X', 'X', 'X', 'X'},
        {'X', '*', 'X', 'O', 'X'},
        {'X', 'O', 'X', '#', 'X'},
        {'X', 'X', 'X', 'X', 'X'}
    };

    EXPECT_EQ(getFood(grid), -1);
}