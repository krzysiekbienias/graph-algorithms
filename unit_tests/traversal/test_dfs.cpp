#include <gtest/gtest.h>
#include "graph.hpp"

#include "traversal/dfs.hpp"

TEST(DfsTest, ReturnsEmptyWhenStartVertexDoesNotExist) {
    Graph g(true);
    g.addVertex(1);
    g.addVertex(2);
    g.addEdge(1, 2);

    const auto result = dfs(g, 99);

    EXPECT_TRUE(result.empty());
}

TEST(DfsTest, ReturnsSingleVertexForIsolatedStartVertex) {
    Graph g(true);
    g.addVertex(1);

    const auto result = dfs(g, 1);

    std::vector<Graph::Vertex> expected{1};
    EXPECT_EQ(result, expected);
}

TEST(DfsTest, TraversesSingleEdgeDirectedGraph) {
    Graph g(true);
    g.addVertex(1);
    g.addVertex(2);
    g.addEdge(1, 2);

    const auto result = dfs(g, 1);

    std::vector<Graph::Vertex> expected{1, 2};
    EXPECT_EQ(result, expected);
}

TEST(DfsTest, ReturnsOnlyReachableVerticesInDirectedGraph) {
    Graph g(true);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);

    g.addEdge(1, 2);
    g.addEdge(2, 3);
    // vertex 4 is disconnected

    const auto result = dfs(g, 1);

    std::vector<Graph::Vertex> expected{1, 2, 3};
    EXPECT_EQ(result, expected);
}

TEST(DfsTest, TraversesDepthFirstInExpectedOrder) {
    Graph g(true);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addVertex(5);

    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(2, 5);

    const auto result = dfs(g, 1);

    // Because neighbors are pushed in reverse order,
    // traversal should visit 2 before 3, and 4 before 5.
    std::vector<Graph::Vertex> expected{1, 2, 4, 5, 3};
    EXPECT_EQ(result, expected);
}

TEST(DfsTest, HandlesCycleWithoutInfiniteLoop) {
    Graph g(true);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);

    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    const auto result = dfs(g, 1);

    std::vector<Graph::Vertex> expected{1, 2, 3};
    EXPECT_EQ(result, expected);
}

TEST(DfsTest, DoesNotVisitSameVertexTwiceWhenMultiplePathsLeadToIt) {
    Graph g(true);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);

    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);

    const auto result = dfs(g, 1);

    std::vector<Graph::Vertex> expected{1, 2, 4, 3};
    EXPECT_EQ(result, expected);
}

TEST(DfsTest, TraversesUndirectedGraphCorrectly) {
    Graph g(false);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);

    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(2, 4);

    const auto result = dfs(g, 1);

    std::vector<Graph::Vertex> expected{1, 2, 3, 4};
    EXPECT_EQ(result, expected);
}

TEST(DfsTest, StartingFromMiddleOfDirectedGraphVisitsOnlyReachableSubgraph) {
    Graph g(true);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addVertex(5);

    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(1, 5);

    const auto result = dfs(g, 3);

    std::vector<Graph::Vertex> expected{3, 4};
    EXPECT_EQ(result, expected);
}

TEST(DfsTest, HandlesSelfLoopCorrectly) {
    Graph g(true);
    g.addVertex(1);
    g.addVertex(2);

    g.addEdge(1, 1);
    g.addEdge(1, 2);

    const auto result = dfs(g, 1);

    std::vector<Graph::Vertex> expected{1, 2};
    EXPECT_EQ(result, expected);
}
