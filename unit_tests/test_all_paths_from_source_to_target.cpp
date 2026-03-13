#include <gtest/gtest.h>
#include <gmock/gmock.h>


#include "graph.hpp"
#include "builders/build_from_adjecency_list.hpp"
#include "all_paths_from_source_to_target.hpp"

using ::testing::ElementsAre;

TEST(AllPathsFromSourceToTarget,TrivalCaseApi) {
    std::vector<std::vector<int>> graphRaw={{4,3,1},{3,2,4},{3},{4},{}};
    std::vector<std::vector<int>> expected={{0,4},{0,3,4},{0,1,3,4},{0,1,2,3,4},{0,1,4}};
    Graph g=buildGraphFromAdjList(graphRaw);
    std::vector<std::vector<int>> actual=allPathsSourceTarget(g);
    EXPECT_THAT(actual,expected);

}

TEST(AllPathsFromSourceToTarget,TrivalCase2Api) {
    std::vector<std::vector<int>> graphRaw={{1,2},{3},{3},{}};
    std::vector<std::vector<int>> expected={{0,1,3},{0,2,3}};
    Graph g=buildGraphFromAdjList(graphRaw);
    std::vector<std::vector<int>> actual=allPathsSourceTarget(g);
    EXPECT_THAT(actual,expected);

}

TEST(AllPathsFromSourceToTarget,SinglePathApi) {
    std::vector<std::vector<int>> graphRaw={{1},{2},{3},{}};
    std::vector<std::vector<int>> expected={{0,1,2,3}};

    Graph g = buildGraphFromAdjList(graphRaw);
    std::vector<std::vector<int>> actual = allPathsSourceTarget(g);

    EXPECT_THAT(actual, expected);
}

TEST(AllPathsFromSourceToTarget,DirectEdgeOnlyApi) {
    std::vector<std::vector<int>> graphRaw={{1},{}};
    std::vector<std::vector<int>> expected={{0,1}};

    Graph g = buildGraphFromAdjList(graphRaw);
    std::vector<std::vector<int>> actual = allPathsSourceTarget(g);

    EXPECT_THAT(actual, expected);
}

TEST(AllPathsFromSourceToTarget,BranchingDagApi) {
    std::vector<std::vector<int>> graphRaw={{1,2,3},{4},{4},{4},{}};
    std::vector<std::vector<int>> expected={
        {0,1,4},
        {0,2,4},
        {0,3,4}
    };

    Graph g = buildGraphFromAdjList(graphRaw);
    std::vector<std::vector<int>> actual = allPathsSourceTarget(g);

    EXPECT_THAT(actual, expected);
}

TEST(AllPathsFromSourceToTarget,LongerBranchingDagApi) {
    std::vector<std::vector<int>> graphRaw={{1,2},{3,4},{4},{5},{5},{}};
    std::vector<std::vector<int>> expected={
        {0,1,3,5},
        {0,1,4,5},
        {0,2,4,5}
    };

    Graph g = buildGraphFromAdjList(graphRaw);
    std::vector<std::vector<int>> actual = allPathsSourceTarget(g);

    EXPECT_THAT(actual, expected);
}

TEST(AllPathsFromSourceToTarget,NoPathToTargetApi) {
    std::vector<std::vector<int>> graphRaw={{1},{2},{},{}};
    std::vector<std::vector<int>> expected={};

    Graph g = buildGraphFromAdjList(graphRaw);
    std::vector<std::vector<int>> actual = allPathsSourceTarget(g);

    EXPECT_THAT(actual, expected);
}

TEST(AllPathsFromSourceToTarget,DiamondShapeApi) {
    std::vector<std::vector<int>> graphRaw={{1,2},{3},{3},{}};
    std::vector<std::vector<int>> expected={
        {0,1,3},
        {0,2,3}
    };

    Graph g = buildGraphFromAdjList(graphRaw);
    std::vector<std::vector<int>> actual = allPathsSourceTarget(g);

    EXPECT_THAT(actual, expected);
}

TEST(AllPathsFromSourceToTarget,MultipleDifferentDepthsApi) {
    std::vector<std::vector<int>> graphRaw={{1,2,3},{4},{4},{},{}};
    std::vector<std::vector<int>> expected={
        {0,1,4},
        {0,2,4}
    };

    Graph g = buildGraphFromAdjList(graphRaw);
    std::vector<std::vector<int>> actual = allPathsSourceTarget(g);

    EXPECT_THAT(actual, expected);
}