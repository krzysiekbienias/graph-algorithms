#include <gtest/gtest.h>
#include "graph.hpp"

TEST(GraphAddVertexTest, ReturnsTrueWhenVertexIsInsertedForTheFirstTime) {
    Graph g;

    const bool inserted = g.addVertex(1);

    EXPECT_TRUE(inserted);
    EXPECT_TRUE(g.containsVertex(1));
    EXPECT_EQ(g.vertexCount(), 1u);
}

TEST(GraphAddVertexTest, ReturnsFalseWhenVertexAlreadyExists) {
    Graph g;

    EXPECT_TRUE(g.addVertex(1));
    const bool insertedAgain = g.addVertex(1);

    EXPECT_FALSE(insertedAgain);
    EXPECT_TRUE(g.containsVertex(1));
    EXPECT_EQ(g.vertexCount(), 1u);
}

TEST(GraphAddVertexTest, CanInsertMultipleDifferentVertices) {
    Graph g;

    EXPECT_TRUE(g.addVertex(1));
    EXPECT_TRUE(g.addVertex(2));
    EXPECT_TRUE(g.addVertex(3));

    EXPECT_TRUE(g.containsVertex(1));
    EXPECT_TRUE(g.containsVertex(2));
    EXPECT_TRUE(g.containsVertex(3));
    EXPECT_EQ(g.vertexCount(), 3u);
}

TEST(GraphAddEdgeTest, AutoCreatesMissingVerticesInDirectedGraph) {
    Graph g(true);

    g.addEdge(1, 2, 7);

    EXPECT_TRUE(g.containsVertex(1));
    EXPECT_TRUE(g.containsVertex(2));
    EXPECT_EQ(g.vertexCount(), 2u);
}

TEST(GraphAddEdgeTest, AddsSingleDirectedEdgeWhenGraphIsDirected) {
    Graph g(true);

    g.addEdge(1, 2, 7);

    const auto& neighborsOf1 = g.getNeighbors(1);
    const auto& neighborsOf2 = g.getNeighbors(2);

    ASSERT_EQ(neighborsOf1.size(), 1u);
    EXPECT_EQ(neighborsOf1[0].to, 2);
    EXPECT_EQ(neighborsOf1[0].weight, 7);

    EXPECT_TRUE(neighborsOf2.empty());
}

TEST(GraphAddEdgeTest, AddsTwoEdgesWhenGraphIsUndirected) {
    Graph g(false);

    g.addEdge(1, 2, 7);

    const auto& neighborsOf1 = g.getNeighbors(1);
    const auto& neighborsOf2 = g.getNeighbors(2);

    ASSERT_EQ(neighborsOf1.size(), 1u);
    EXPECT_EQ(neighborsOf1[0].to, 2);
    EXPECT_EQ(neighborsOf1[0].weight, 7);

    ASSERT_EQ(neighborsOf2.size(), 1u);
    EXPECT_EQ(neighborsOf2[0].to, 1);
    EXPECT_EQ(neighborsOf2[0].weight, 7);
}

TEST(GraphAddEdgeTest, CanAddMultipleEdgesFromSameVertex) {
    Graph g(true);

    g.addEdge(1, 2, 5);
    g.addEdge(1, 3, 9);

    const auto& neighbors = g.getNeighbors(1);

    ASSERT_EQ(neighbors.size(), 2u);

    EXPECT_EQ(neighbors[0].to, 2);
    EXPECT_EQ(neighbors[0].weight, 5);

    EXPECT_EQ(neighbors[1].to, 3);
    EXPECT_EQ(neighbors[1].weight, 9);
}

TEST(GraphAddEdgeTest, CanAddEdgeWithDefaultWeight) {
    Graph g(true);

    g.addEdge(4, 5);

    const auto& neighbors = g.getNeighbors(4);

    ASSERT_EQ(neighbors.size(), 1u);
    EXPECT_EQ(neighbors[0].to, 5);
    EXPECT_EQ(neighbors[0].weight, 1);
}


TEST(GraphGetNeighborsTest, ReturnsOutgoingNeighborsInDirectedGraph) {
    Graph g(true);

    g.addEdge(1, 2, 5);
    g.addEdge(1, 3, 7);

    const auto& neighbors = g.getNeighbors(1);

    ASSERT_EQ(neighbors.size(), 2u);

    EXPECT_EQ(neighbors[0].to, 2);
    EXPECT_EQ(neighbors[0].weight, 5);

    EXPECT_EQ(neighbors[1].to, 3);
    EXPECT_EQ(neighbors[1].weight, 7);
}

TEST(GraphGetNeighborsTest, ReturnsEmptyVectorWhenVertexHasNoOutgoingEdges) {
    Graph g(true);

    g.addVertex(10);

    const auto& neighbors = g.getNeighbors(10);

    EXPECT_TRUE(neighbors.empty());
}

TEST(GraphGetNeighborsTest, DirectedGraphDoesNotAddReverseNeighbor) {
    Graph g(true);

    g.addEdge(1, 2, 9);

    const auto& neighborsOf1 = g.getNeighbors(1);
    const auto& neighborsOf2 = g.getNeighbors(2);

    ASSERT_EQ(neighborsOf1.size(), 1u);
    EXPECT_EQ(neighborsOf1[0].to, 2);
    EXPECT_EQ(neighborsOf1[0].weight, 9);

    EXPECT_TRUE(neighborsOf2.empty());
}

TEST(GraphGetNeighborsTest, UndirectedGraphReturnsReverseNeighborAsWell) {
    Graph g(false);

    g.addEdge(1, 2, 9);

    const auto& neighborsOf1 = g.getNeighbors(1);
    const auto& neighborsOf2 = g.getNeighbors(2);

    ASSERT_EQ(neighborsOf1.size(), 1u);
    EXPECT_EQ(neighborsOf1[0].to, 2);
    EXPECT_EQ(neighborsOf1[0].weight, 9);

    ASSERT_EQ(neighborsOf2.size(), 1u);
    EXPECT_EQ(neighborsOf2[0].to, 1);
    EXPECT_EQ(neighborsOf2[0].weight, 9);
}

TEST(GraphGetNeighborsTest, ReturnsAllNeighborsAddedEarlier) {
    Graph g(false);

    g.addEdge(1, 2, 4);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 15);

    const auto& neighbors = g.getNeighbors(1);

    ASSERT_EQ(neighbors.size(), 3u);

    EXPECT_EQ(neighbors[0].to, 2);
    EXPECT_EQ(neighbors[0].weight, 4);

    EXPECT_EQ(neighbors[1].to, 3);
    EXPECT_EQ(neighbors[1].weight, 8);

    EXPECT_EQ(neighbors[2].to, 4);
    EXPECT_EQ(neighbors[2].weight, 15);
}

TEST(GraphGetVerticesTest, ReturnsEmptyVectorForEmptyGraph) {
    Graph g;

    const auto vertices = g.getVertices();

    EXPECT_TRUE(vertices.empty());
}

TEST(GraphGetVerticesTest, ReturnsSingleInsertedVertex) {
    Graph g;

    g.addVertex(42);

    const auto vertices = g.getVertices();

    ASSERT_EQ(vertices.size(), 1u);
    EXPECT_EQ(vertices[0], 42);
}

TEST(GraphGetVerticesTest, ReturnsAllInsertedVertices) {
    Graph g;

    g.addVertex(10);
    g.addVertex(20);
    g.addVertex(30);

    auto vertices = g.getVertices();
    std::sort(vertices.begin(), vertices.end());

    ASSERT_EQ(vertices.size(), 3u);
    EXPECT_EQ(vertices[0], 10);
    EXPECT_EQ(vertices[1], 20);
    EXPECT_EQ(vertices[2], 30);
}

TEST(GraphGetVerticesTest, IncludesVerticesAddedThroughAddEdge) {
    Graph g(true);

    g.addEdge(1, 2, 5);
    g.addEdge(2, 3, 7);

    auto vertices = g.getVertices();
    std::sort(vertices.begin(), vertices.end());

    ASSERT_EQ(vertices.size(), 3u);
    EXPECT_EQ(vertices[0], 1);
    EXPECT_EQ(vertices[1], 2);
    EXPECT_EQ(vertices[2], 3);
}

TEST(GraphGetVerticesTest, DoesNotDuplicateVerticesWhenSameVertexIsAddedMultipleTimes) {
    Graph g;

    g.addVertex(5);
    g.addVertex(5);
    g.addEdge(5, 6);
    g.addEdge(5, 6);

    auto vertices = g.getVertices();
    std::sort(vertices.begin(), vertices.end());

    ASSERT_EQ(vertices.size(), 2u);
    EXPECT_EQ(vertices[0], 5);
    EXPECT_EQ(vertices[1], 6);
}