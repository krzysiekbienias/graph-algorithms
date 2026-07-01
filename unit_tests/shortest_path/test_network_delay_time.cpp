#include <gtest/gtest.h>
#include "graph.hpp"
#include "shortest_path/network_delay_time.hpp"


TEST(NetworkDelayTime, BasicCase) {
    std::vector<std::vector<int>> signalTimes={{2,1,1},{2,3,1},{3,4,1}};
    int actual=networkDelayTime(signalTimes,4,2);
    EXPECT_EQ(actual,2);

}