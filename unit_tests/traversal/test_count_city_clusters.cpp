#include <gtest/gtest.h>
#include "traversal/count_city_clusters.hpp"


TEST(FindCircleNumTest, ReturnsTwoProvincesForExampleCase) {
    std::vector<std::vector<int>> isConnected = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1}
    };

    EXPECT_EQ(countCityClusters(isConnected), 2);
}

TEST(FindCircleNumTest, ReturnsThreeProvincesWhenAllCitiesAreIsolated) {
    std::vector<std::vector<int>> isConnected = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    EXPECT_EQ(countCityClusters(isConnected), 3);
}

TEST(FindCircleNumTest, ReturnsOneProvinceWhenAllCitiesAreConnected) {
    std::vector<std::vector<int>> isConnected = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    EXPECT_EQ(countCityClusters(isConnected), 1);
}

TEST(FindCircleNumTest, ReturnsOneProvinceForSingleCity) {
    std::vector<std::vector<int>> isConnected = {
        {1}
    };

    EXPECT_EQ(countCityClusters(isConnected), 1);
}

TEST(FindCircleNumTest, ReturnsTwoProvincesForTwoSeparateGroups) {
    std::vector<std::vector<int>> isConnected = {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 1, 1},
        {0, 0, 1, 1}
    };

    EXPECT_EQ(countCityClusters(isConnected), 2);
}

TEST(FindCircleNumTest, ReturnsOneProvinceForIndirectConnections) {
    std::vector<std::vector<int>> isConnected = {
        {1, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 1, 1, 1},
        {0, 0, 1, 1}
    };

    EXPECT_EQ(countCityClusters(isConnected), 1);
}

TEST(FindCircleNumTest, ReturnsFourProvincesForFourDisconnectedCities) {
    std::vector<std::vector<int>> isConnected = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    EXPECT_EQ(countCityClusters(isConnected), 4);
}