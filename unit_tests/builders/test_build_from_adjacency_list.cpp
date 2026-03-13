#include <gtest/gtest.h>
#include "graph.hpp"
#include "builders/build_from_adjecency_list.hpp"


TEST(BuildGraphFromAdjListTest, BuildsDirectedGraphCorrectly) {
    std::vector<std::vector<Graph::Vertex>> adjList{
        {4, 3, 1},
        {3, 2, 4},
        {3},
        {4},
        {}
    };

    Graph g = buildGraphFromAdjList(adjList, true);

    EXPECT_TRUE(g.isDirected());
    EXPECT_EQ(g.vertexCount(), 5u);

    for (int v = 0; v < 5; ++v) {
        EXPECT_TRUE(g.containsVertex(v));
    }

    const auto& neighbors0 = g.getNeighbors(0);
    ASSERT_EQ(neighbors0.size(), 3u);
    EXPECT_EQ(neighbors0[0].to, 4);
    EXPECT_EQ(neighbors0[0].weight, 1);
    EXPECT_EQ(neighbors0[1].to, 3);
    EXPECT_EQ(neighbors0[1].weight, 1);
    EXPECT_EQ(neighbors0[2].to, 1);
    EXPECT_EQ(neighbors0[2].weight, 1);

    const auto& neighbors1 = g.getNeighbors(1);
    ASSERT_EQ(neighbors1.size(), 3u);
    EXPECT_EQ(neighbors1[0].to, 3);
    EXPECT_EQ(neighbors1[0].weight, 1);
    EXPECT_EQ(neighbors1[1].to, 2);
    EXPECT_EQ(neighbors1[1].weight, 1);
    EXPECT_EQ(neighbors1[2].to, 4);
    EXPECT_EQ(neighbors1[2].weight, 1);

    const auto& neighbors2 = g.getNeighbors(2);
    ASSERT_EQ(neighbors2.size(), 1u);
    EXPECT_EQ(neighbors2[0].to, 3);
    EXPECT_EQ(neighbors2[0].weight, 1);

    const auto& neighbors3 = g.getNeighbors(3);
    ASSERT_EQ(neighbors3.size(), 1u);
    EXPECT_EQ(neighbors3[0].to, 4);
    EXPECT_EQ(neighbors3[0].weight, 1);

    EXPECT_TRUE(g.getNeighbors(4).empty());
}

TEST(BuildGraphFromAdjListTest, BuildsUndirectedGraphCorrectly) {
    std::vector<std::vector<Graph::Vertex>> adjList{
        {1, 2},
        {0, 3},
        {0},
        {1}
    };

    Graph g = buildGraphFromAdjList(adjList, false);

    EXPECT_FALSE(g.isDirected());
    EXPECT_EQ(g.vertexCount(), 4u);

    const auto& neighbors0 = g.getNeighbors(0);
    ASSERT_EQ(neighbors0.size(), 4u);
    EXPECT_EQ(neighbors0[0].to, 1);
    EXPECT_EQ(neighbors0[0].weight, 1);
    EXPECT_EQ(neighbors0[1].to, 2);
    EXPECT_EQ(neighbors0[1].weight, 1);
    EXPECT_EQ(neighbors0[2].to, 1);
    EXPECT_EQ(neighbors0[2].weight, 1);
    EXPECT_EQ(neighbors0[3].to, 2);
    EXPECT_EQ(neighbors0[3].weight, 1);

    const auto& neighbors1 = g.getNeighbors(1);
    ASSERT_EQ(neighbors1.size(), 4u);
    EXPECT_EQ(neighbors1[0].to, 0);
    EXPECT_EQ(neighbors1[0].weight, 1);
    EXPECT_EQ(neighbors1[1].to, 0);
    EXPECT_EQ(neighbors1[1].weight, 1);
    EXPECT_EQ(neighbors1[2].to, 3);
    EXPECT_EQ(neighbors1[2].weight, 1);
    EXPECT_EQ(neighbors1[3].to, 3);
    EXPECT_EQ(neighbors1[3].weight, 1);

    const auto& neighbors2 = g.getNeighbors(2);
    ASSERT_EQ(neighbors2.size(), 2u);
    EXPECT_EQ(neighbors2[0].to, 0);
    EXPECT_EQ(neighbors2[0].weight, 1);
    EXPECT_EQ(neighbors2[1].to, 0);
    EXPECT_EQ(neighbors2[1].weight, 1);

    const auto& neighbors3 = g.getNeighbors(3);
    ASSERT_EQ(neighbors3.size(), 2u);
    EXPECT_EQ(neighbors3[0].to, 1);
    EXPECT_EQ(neighbors3[0].weight, 1);
    EXPECT_EQ(neighbors3[1].to, 1);
    EXPECT_EQ(neighbors3[1].weight, 1);
}


TEST(BuildGraphFromWeightedAdjListTest, BuildsDirectedWeightedGraphCorrectly) {
    std::vector<std::vector<std::vector<int>>> adjList{
        {{1, 7}},
        {{2, 6}, {3, 20}, {4, 3}},
        {{3, 14}},
        {{4, 2}},
        {},
        {}
    };

    Graph g = buildGraphFromWeightedAdjList(adjList, true);

    EXPECT_TRUE(g.isDirected());
    EXPECT_EQ(g.vertexCount(), 6u);

    for (int v = 0; v < 6; ++v) {
        EXPECT_TRUE(g.containsVertex(v));
    }

    const auto& neighbors0 = g.getNeighbors(0);
    ASSERT_EQ(neighbors0.size(), 1u);
    EXPECT_EQ(neighbors0[0].to, 1);
    EXPECT_EQ(neighbors0[0].weight, 7);

    const auto& neighbors1 = g.getNeighbors(1);
    ASSERT_EQ(neighbors1.size(), 3u);
    EXPECT_EQ(neighbors1[0].to, 2);
    EXPECT_EQ(neighbors1[0].weight, 6);
    EXPECT_EQ(neighbors1[1].to, 3);
    EXPECT_EQ(neighbors1[1].weight, 20);
    EXPECT_EQ(neighbors1[2].to, 4);
    EXPECT_EQ(neighbors1[2].weight, 3);

    const auto& neighbors2 = g.getNeighbors(2);
    ASSERT_EQ(neighbors2.size(), 1u);
    EXPECT_EQ(neighbors2[0].to, 3);
    EXPECT_EQ(neighbors2[0].weight, 14);

    const auto& neighbors3 = g.getNeighbors(3);
    ASSERT_EQ(neighbors3.size(), 1u);
    EXPECT_EQ(neighbors3[0].to, 4);
    EXPECT_EQ(neighbors3[0].weight, 2);

    EXPECT_TRUE(g.getNeighbors(4).empty());
    EXPECT_TRUE(g.getNeighbors(5).empty());
}

TEST(BuildGraphFromWeightedAdjListTest, BuildsUndirectedWeightedGraphCorrectlyFromHalfSpecifiedAdjList) {
    std::vector<std::vector<std::vector<int>>> adjList{
        {{1, 5}, {2, 8}},
        {{3, 4}},
        {},
        {}
    };

    Graph g = buildGraphFromWeightedAdjList(adjList, false);

    EXPECT_FALSE(g.isDirected());
    EXPECT_EQ(g.vertexCount(), 4u);

    const auto& neighbors0 = g.getNeighbors(0);
    ASSERT_EQ(neighbors0.size(), 2u);
    EXPECT_EQ(neighbors0[0].to, 1);
    EXPECT_EQ(neighbors0[0].weight, 5);
    EXPECT_EQ(neighbors0[1].to, 2);
    EXPECT_EQ(neighbors0[1].weight, 8);

    const auto& neighbors1 = g.getNeighbors(1);
    ASSERT_EQ(neighbors1.size(), 2u);
    EXPECT_EQ(neighbors1[0].to, 0);
    EXPECT_EQ(neighbors1[0].weight, 5);
    EXPECT_EQ(neighbors1[1].to, 3);
    EXPECT_EQ(neighbors1[1].weight, 4);

    const auto& neighbors2 = g.getNeighbors(2);
    ASSERT_EQ(neighbors2.size(), 1u);
    EXPECT_EQ(neighbors2[0].to, 0);
    EXPECT_EQ(neighbors2[0].weight, 8);

    const auto& neighbors3 = g.getNeighbors(3);
    ASSERT_EQ(neighbors3.size(), 1u);
    EXPECT_EQ(neighbors3[0].to, 1);
    EXPECT_EQ(neighbors3[0].weight, 4);
}

TEST(BuildGraphFromWeightedAdjListTest, BuildsGraphWithNoEdges) {
    std::vector<std::vector<std::vector<int>>> adjList{
        {},
        {},
        {},
        {}
    };

    Graph g = buildGraphFromWeightedAdjList(adjList, true);

    EXPECT_TRUE(g.isDirected());
    EXPECT_EQ(g.vertexCount(), 4u);

    for (int v = 0; v < 4; ++v) {
        EXPECT_TRUE(g.containsVertex(v));
        EXPECT_TRUE(g.getNeighbors(v).empty());
    }
}

TEST(BuildGraphFromWeightedAdjListTest, BuildsGraphWithSingleVertex) {
    std::vector<std::vector<std::vector<int>>> adjList{
        {}
    };

    Graph g = buildGraphFromWeightedAdjList(adjList, true);

    EXPECT_TRUE(g.containsVertex(0));
    EXPECT_EQ(g.vertexCount(), 1u);
    EXPECT_TRUE(g.getNeighbors(0).empty());
}

TEST(BuildGraphFromWeightedAdjListTest, KeepsIsolatedVertices) {
    std::vector<std::vector<std::vector<int>>> adjList{
        {{1, 10}},
        {},
        {},
        {}
    };

    Graph g = buildGraphFromWeightedAdjList(adjList, true);

    EXPECT_EQ(g.vertexCount(), 4u);

    EXPECT_TRUE(g.containsVertex(0));
    EXPECT_TRUE(g.containsVertex(1));
    EXPECT_TRUE(g.containsVertex(2));
    EXPECT_TRUE(g.containsVertex(3));

    const auto& neighbors0 = g.getNeighbors(0);
    ASSERT_EQ(neighbors0.size(), 1u);
    EXPECT_EQ(neighbors0[0].to, 1);
    EXPECT_EQ(neighbors0[0].weight, 10);

    EXPECT_TRUE(g.getNeighbors(1).empty());
    EXPECT_TRUE(g.getNeighbors(2).empty());
    EXPECT_TRUE(g.getNeighbors(3).empty());
}

TEST(BuildGraphFromWeightedAdjListTest, PreservesZeroAndNegativeWeights) {
    std::vector<std::vector<std::vector<int>>> adjList{
        {{1, 0}},
        {{2, -3}},
        {}
    };

    Graph g = buildGraphFromWeightedAdjList(adjList, true);

    const auto& neighbors0 = g.getNeighbors(0);
    ASSERT_EQ(neighbors0.size(), 1u);
    EXPECT_EQ(neighbors0[0].to, 1);
    EXPECT_EQ(neighbors0[0].weight, 0);

    const auto& neighbors1 = g.getNeighbors(1);
    ASSERT_EQ(neighbors1.size(), 1u);
    EXPECT_EQ(neighbors1[0].to, 2);
    EXPECT_EQ(neighbors1[0].weight, -3);
}

TEST(BuildGraphFromWeightedAdjListTest, AllowsSelfLoop) {
    std::vector<std::vector<std::vector<int>>> adjList{
        {{0, 9}, {1, 2}},
        {}
    };

    Graph g = buildGraphFromWeightedAdjList(adjList, true);

    const auto& neighbors0 = g.getNeighbors(0);
    ASSERT_EQ(neighbors0.size(), 2u);

    EXPECT_EQ(neighbors0[0].to, 0);
    EXPECT_EQ(neighbors0[0].weight, 9);

    EXPECT_EQ(neighbors0[1].to, 1);
    EXPECT_EQ(neighbors0[1].weight, 2);
}