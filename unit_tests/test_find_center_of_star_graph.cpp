#include <gtest/gtest.h>

#include "find_center_of_star_graph.hpp"
#include "graph.hpp"
#include <unordered_set>
#include "builders/adjacency_list_style.hpp"

TEST(CenterStarGraph,Simple) {
    std::vector<std::vector<int>> edges ={{1,2},{2,3},{4,2}};
    std::unordered_set<int> vertices ={1,2,3,4};
    auto graph=buildGraphFromEdgeList(vertices,edges,false);
    EXPECT_EQ(findCenter(graph),2);

}

TEST(CenterStarGraph,Simple2) {
    std::vector<std::vector<int>> edges ={{1,2},{5,1},{1,3},{1,4}};
    std::unordered_set<int> vertices ={1,2,3,4,5};
    auto graph=buildGraphFromEdgeList(vertices,edges,false);
    EXPECT_EQ(findCenter(graph),1);

}