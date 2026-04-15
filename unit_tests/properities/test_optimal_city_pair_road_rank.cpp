#include <gtest/gtest.h>
#include "graph.hpp"
#include "properities/optimal_city_pair_road_rank.hpp"

TEST(MaximalNetworkRankTest, BasicCaseFourCities)
{
    int n = 4;
    std::vector<std::vector<int>> roads = {{0, 1}, {0, 3}, {1, 2}, {1, 3}};
    int expected = 4;
    int actual = maximalNetworkRank(n, roads);

    EXPECT_EQ(actual, expected);
}

TEST(MaximalNetworkRankTest, BasicCaseFiveCities)
{
    int n = 5;
    std::vector<std::vector<int>> roads = {{0, 1}, {0, 3}, {1, 2}, {1, 3}, {2, 3}, {2, 4}};
    int expected = 5;
    int actual = maximalNetworkRank(n, roads);

    EXPECT_EQ(actual, expected);
}

TEST(MaximalNetworkRankTest, DisconnectedCities)
{
    int n = 8;
    std::vector<std::vector<int>> roads = {{0, 1}, {1, 2}, {2, 3}, {2, 4}, {5, 6}, {5, 7}};
    int expected = 5;
    int actual = maximalNetworkRank(n, roads);

    EXPECT_EQ(actual, expected);
}

TEST(MaximalNetworkRankTest, NoRoads)
{
    int n = 4;
    std::vector<std::vector<int>> roads = {};
    int expected = 0;
    int actual = maximalNetworkRank(n, roads);

    EXPECT_EQ(actual, expected);
}

TEST(MaximalNetworkRankTest, TwoCitiesOneRoad)
{
    int n = 2;
    std::vector<std::vector<int>> roads = {{0, 1}};
    int expected = 1;
    int actual = maximalNetworkRank(n, roads);

    EXPECT_EQ(actual, expected);
}
