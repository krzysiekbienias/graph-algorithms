#include <gtest/gtest.h>
#include "graph.hpp"

#include <gtest/gtest.h>
#include <unordered_set>
#include <vector>
#include <stdexcept>
#include "graph.hpp"
#include "builders/build_from_edge_list.hpp"   // or the header where buildGraphFromEdgeList is declared

namespace {

bool containsEdge(const Graph& g,
                  Graph::Vertex from,
                  Graph::Vertex to,
                  Graph::Weight weight = 1) {
    if (!g.containsVertex(from)) {
        return false;
    }

    const auto& neighbors = g.getNeighbors(from);
    for (const auto& edge : neighbors) {
        if (edge.to == to && edge.weight == weight) {
            return true;
        }
    }
    return false;
}

} // namespace

TEST(BuildGraphFromEdgeListTest, BuildsDirectedGraphCorrectly) {
    std::unordered_set<Graph::Vertex> vertices{1, 2, 3, 4};
    std::vector<std::vector<int>> edges{
        {1, 2},
        {2, 3},
        {3, 4}
    };

    Graph g = buildGraphFromEdgeList(vertices, edges, true);

    EXPECT_TRUE(g.isDirected());
    EXPECT_EQ(g.vertexCount(), 4);

    EXPECT_TRUE(g.containsVertex(1));
    EXPECT_TRUE(g.containsVertex(2));
    EXPECT_TRUE(g.containsVertex(3));
    EXPECT_TRUE(g.containsVertex(4));

    EXPECT_TRUE(containsEdge(g, 1, 2));
    EXPECT_TRUE(containsEdge(g, 2, 3));
    EXPECT_TRUE(containsEdge(g, 3, 4));

    EXPECT_FALSE(containsEdge(g, 2, 1));
    EXPECT_FALSE(containsEdge(g, 3, 2));
    EXPECT_FALSE(containsEdge(g, 4, 3));
}

TEST(BuildGraphFromEdgeListTest, BuildsUndirectedGraphCorrectly) {
    std::unordered_set<Graph::Vertex> vertices{1, 2, 3};
    std::vector<std::vector<int>> edges{
        {1, 2},
        {2, 3}
    };

    Graph g = buildGraphFromEdgeList(vertices, edges, false);

    EXPECT_FALSE(g.isDirected());
    EXPECT_EQ(g.vertexCount(), 3);

    EXPECT_TRUE(containsEdge(g, 1, 2));
    EXPECT_TRUE(containsEdge(g, 2, 1));

    EXPECT_TRUE(containsEdge(g, 2, 3));
    EXPECT_TRUE(containsEdge(g, 3, 2));
}

TEST(BuildGraphFromEdgeListTest, BuildsGraphWithVerticesOnly) {
    std::unordered_set<Graph::Vertex> vertices{10, 20, 30};
    std::vector<std::vector<int>> edges{};

    Graph g = buildGraphFromEdgeList(vertices, edges, true);

    EXPECT_TRUE(g.isDirected());
    EXPECT_EQ(g.vertexCount(), 3);

    EXPECT_TRUE(g.containsVertex(10));
    EXPECT_TRUE(g.containsVertex(20));
    EXPECT_TRUE(g.containsVertex(30));

    EXPECT_TRUE(g.getNeighbors(10).empty());
    EXPECT_TRUE(g.getNeighbors(20).empty());
    EXPECT_TRUE(g.getNeighbors(30).empty());
}

TEST(BuildGraphFromEdgeListTest, ThrowsWhenEdgeDoesNotHaveExactlyTwoElements) {
    std::unordered_set<Graph::Vertex> vertices{1, 2, 3};

    std::vector<std::vector<int>> edges1{
        {1}
    };

    std::vector<std::vector<int>> edges2{
        {1, 2, 3}
    };

    EXPECT_THROW(buildGraphFromEdgeList(vertices, edges1, true), std::invalid_argument);
    EXPECT_THROW(buildGraphFromEdgeList(vertices, edges2, true), std::invalid_argument);
}

TEST(BuildGraphFromEdgeListTest, ThrowsWhenEdgeReferencesMissingSourceVertex) {
    std::unordered_set<Graph::Vertex> vertices{1, 2, 3};
    std::vector<std::vector<int>> edges{
        {4, 2}
    };

    EXPECT_THROW(buildGraphFromEdgeList(vertices, edges, true), std::invalid_argument);
}

TEST(BuildGraphFromEdgeListTest, ThrowsWhenEdgeReferencesMissingTargetVertex) {
    std::unordered_set<Graph::Vertex> vertices{1, 2, 3};
    std::vector<std::vector<int>> edges{
        {1, 4}
    };

    EXPECT_THROW(buildGraphFromEdgeList(vertices, edges, true), std::invalid_argument);
}

TEST(BuildGraphFromEdgeListTest, AcceptsNonContiguousVertexLabels) {
    std::unordered_set<Graph::Vertex> vertices{10, 42, 99};
    std::vector<std::vector<int>> edges{
        {10, 99},
        {42, 10}
    };

    Graph g = buildGraphFromEdgeList(vertices, edges, true);

    EXPECT_TRUE(g.isDirected());
    EXPECT_EQ(g.vertexCount(), 3);

    EXPECT_TRUE(g.containsVertex(10));
    EXPECT_TRUE(g.containsVertex(42));
    EXPECT_TRUE(g.containsVertex(99));

    EXPECT_TRUE(containsEdge(g, 10, 99));
    EXPECT_TRUE(containsEdge(g, 42, 10));
    EXPECT_FALSE(containsEdge(g, 99, 10));
}

TEST(BuildGraphFromWeightedEdgeListTest, BuildsDirectedWeightedGraphCorrectly) {
    std::vector<std::vector<int>> edges{
        {0, 1, 4},
        {0, 2, 7},
        {1, 3, 2}
    };

    Graph g = buildGraphFromWeightedEdgeList(4, edges, true);

    EXPECT_TRUE(g.isDirected());
    EXPECT_EQ(g.vertexCount(), 4u);

    EXPECT_TRUE(g.containsVertex(0));
    EXPECT_TRUE(g.containsVertex(1));
    EXPECT_TRUE(g.containsVertex(2));
    EXPECT_TRUE(g.containsVertex(3));

    const auto& neighbors0 = g.getNeighbors(0);
    ASSERT_EQ(neighbors0.size(), 2u);
    EXPECT_EQ(neighbors0[0].to, 1);
    EXPECT_EQ(neighbors0[0].weight, 4);
    EXPECT_EQ(neighbors0[1].to, 2);
    EXPECT_EQ(neighbors0[1].weight, 7);

    const auto& neighbors1 = g.getNeighbors(1);
    ASSERT_EQ(neighbors1.size(), 1u);
    EXPECT_EQ(neighbors1[0].to, 3);
    EXPECT_EQ(neighbors1[0].weight, 2);

    EXPECT_TRUE(g.getNeighbors(2).empty());
    EXPECT_TRUE(g.getNeighbors(3).empty());
}

TEST(BuildGraphFromWeightedEdgeListTest, BuildsUndirectedWeightedGraphCorrectly) {
    std::vector<std::vector<int>> edges{
        {0, 1, 5},
        {1, 2, 8}
    };

    Graph g = buildGraphFromWeightedEdgeList(3, edges, false);

    EXPECT_FALSE(g.isDirected());
    EXPECT_EQ(g.vertexCount(), 3u);

    const auto& neighbors0 = g.getNeighbors(0);
    ASSERT_EQ(neighbors0.size(), 1u);
    EXPECT_EQ(neighbors0[0].to, 1);
    EXPECT_EQ(neighbors0[0].weight, 5);

    const auto& neighbors1 = g.getNeighbors(1);
    ASSERT_EQ(neighbors1.size(), 2u);

    EXPECT_EQ(neighbors1[0].to, 0);
    EXPECT_EQ(neighbors1[0].weight, 5);

    EXPECT_EQ(neighbors1[1].to, 2);
    EXPECT_EQ(neighbors1[1].weight, 8);

    const auto& neighbors2 = g.getNeighbors(2);
    ASSERT_EQ(neighbors2.size(), 1u);
    EXPECT_EQ(neighbors2[0].to, 1);
    EXPECT_EQ(neighbors2[0].weight, 8);
}

TEST(BuildGraphFromWeightedEdgeListTest, BuildsGraphWithNoEdges) {
    std::vector<std::vector<int>> edges{};

    Graph g = buildGraphFromWeightedEdgeList(5, edges, true);

    EXPECT_TRUE(g.isDirected());
    EXPECT_EQ(g.vertexCount(), 5u);

    for (int v = 0; v < 5; ++v) {
        EXPECT_TRUE(g.containsVertex(v));
        EXPECT_TRUE(g.getNeighbors(v).empty());
    }
}

TEST(BuildGraphFromWeightedEdgeListTest, BuildsGraphWithSingleVertexAndNoEdges) {
    std::vector<std::vector<int>> edges{};

    Graph g = buildGraphFromWeightedEdgeList(1, edges, true);

    EXPECT_EQ(g.vertexCount(), 1u);
    EXPECT_TRUE(g.containsVertex(0));
    EXPECT_TRUE(g.getNeighbors(0).empty());
}

TEST(BuildGraphFromWeightedEdgeListTest, PreservesZeroAndNegativeWeights) {
    std::vector<std::vector<int>> edges{
        {0, 1, 0},
        {1, 2, -3}
    };

    Graph g = buildGraphFromWeightedEdgeList(3, edges, true);

    const auto& neighbors0 = g.getNeighbors(0);
    ASSERT_EQ(neighbors0.size(), 1u);
    EXPECT_EQ(neighbors0[0].to, 1);
    EXPECT_EQ(neighbors0[0].weight, 0);

    const auto& neighbors1 = g.getNeighbors(1);
    ASSERT_EQ(neighbors1.size(), 1u);
    EXPECT_EQ(neighbors1[0].to, 2);
    EXPECT_EQ(neighbors1[0].weight, -3);
}

TEST(BuildGraphFromWeightedEdgeListTest, KeepsIsolatedVertices) {
    std::vector<std::vector<int>> edges{
        {0, 1, 10}
    };

    Graph g = buildGraphFromWeightedEdgeList(4, edges, true);

    EXPECT_EQ(g.vertexCount(), 4u);

    EXPECT_TRUE(g.containsVertex(0));
    EXPECT_TRUE(g.containsVertex(1));
    EXPECT_TRUE(g.containsVertex(2));
    EXPECT_TRUE(g.containsVertex(3));

    EXPECT_TRUE(g.getNeighbors(2).empty());
    EXPECT_TRUE(g.getNeighbors(3).empty());
}