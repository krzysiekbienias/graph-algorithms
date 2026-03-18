#include <gtest/gtest.h>
#include "graph.hpp"
#include "properities/is_bipartite.hpp"
#include "builders/build_from_adjecency_list.hpp"

TEST(IsBipartiate,PositiveFromAPI) {
    std::vector<std::vector<int>> edgeList1={{1,4},{0,2},{1},{4},{0,3}};
    auto graph1=buildGraphFromAdjList(edgeList1,5,false);
    EXPECT_TRUE(isBipartite(graph1));
}
