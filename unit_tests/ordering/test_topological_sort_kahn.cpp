#include <gtest/gtest.h>
#include "graph.hpp"
#include "builders/build_from_edge_list.hpp"
#include <unordered_set>
#include <gmock/gmock.h>

#include "ordering/topological_sort_kahn.hpp"

using testing::ElementsAre;

namespace  {
    void expectValidTopologicalOrder(
        const Graph& graph,
        const std::vector<Graph::Vertex>& order
    ) {
        const auto vertices = graph.getVertices();

        // 1. Size must match number of vertices.
        ASSERT_EQ(order.size(), vertices.size())
            << "Topological order must contain exactly all vertices.";

        // 2. Every vertex must appear exactly once.
        std::unordered_set<Graph::Vertex> seen;
        for (const auto& v : order) {
            ASSERT_TRUE(graph.containsVertex(v))
                << "Order contains a vertex that does not belong to the graph: " << v;

            ASSERT_TRUE(seen.insert(v).second)
                << "Duplicate vertex found in topological order: " << v;
        }

        // 3. Build position map: vertex -> index in order.
        std::unordered_map<Graph::Vertex, int> position;
        for (int i = 0; i < static_cast<int>(order.size()); ++i) {
            position[order[i]] = i;
        }

        // 4. For every directed edge u -> v, u must appear before v.
        for (const auto& u : vertices) {
            for (const auto& edge : graph.getNeighbors(u)) {
                const auto& v = edge.to;
                ASSERT_LT(position[u], position[v])
                    << "Invalid topological order: edge " << u << " -> " << v
                    << " violates the ordering.";
            }
        }
    }
}

TEST(TopologicalSortKhan, BaseCase) {
    std::unordered_set<int> vertices={1,2,3,4};
    std::vector<std::vector<int>> prerequisities={{1,2},{1,3},{3,2},{4,2},{4,3}};
    Graph g=buildGraphFromEdgeList(vertices,prerequisities,true);
    std::vector<int>actual= topologicalSortKhan(g);
    expectValidTopologicalOrder(g, actual);

}

//small graphs also might be testes as follow :

TEST(TopologicalSortKhan, BaseCaseSecondVersion) {
    std::unordered_set<int> vertices={1,2,3,4};
    std::vector<std::vector<int>> prerequisities={{1,2},{1,3},{3,2},{4,2},{4,3}};
    Graph g=buildGraphFromEdgeList(vertices,prerequisities,true);
    std::vector<int>actual= topologicalSortKhan(g);
    const std::vector<std::vector<int>> validOrders{
            {1, 4, 3, 2},
            {4, 1, 3, 2}
    };
    EXPECT_TRUE(std::find(validOrders.begin(), validOrders.end(), actual) != validOrders.end());
}


// ── Interview-friendly variant: toplogicalSortKhan(n, edges) ──────────────────

namespace {
    void expectValidTopologicalOrderRaw(
        int n,
        const std::vector<std::vector<int>>& edges,
        const std::vector<int>& order
    ) {
        ASSERT_EQ(static_cast<int>(order.size()), n)
            << "Topological order must contain exactly n vertices.";

        std::unordered_set<int> seen;
        for (int v : order) {
            ASSERT_GE(v, 0);
            ASSERT_LT(v, n);
            ASSERT_TRUE(seen.insert(v).second)
                << "Duplicate vertex in order: " << v;
        }

        std::unordered_map<int, int> pos;
        for (int i = 0; i < n; ++i) pos[order[i]] = i;

        for (const auto& e : edges) {
            ASSERT_LT(pos[e[0]], pos[e[1]])
                << "Edge " << e[0] << " -> " << e[1] << " violates ordering.";
        }
    }
}

TEST(TopologicalSortKhan, SimpleDAG) {
    // 0 -> 2, 1 -> 2, valid orders: {0,1,2} or {1,0,2}
    int n = 3;
    std::vector<std::vector<int>> edges = {{0, 2}, {1, 2}};
    auto actual = toplogicalSortKhan(n, edges);
    expectValidTopologicalOrderRaw(n, edges, actual);
}

TEST(TopologicalSortKhan, LinearChain) {
    // 0->1->2->3->4, only one valid order
    int n = 5;
    std::vector<std::vector<int>> edges = {{0,1},{1,2},{2,3},{3,4}};
    auto actual = toplogicalSortKhan(n, edges);
    ASSERT_EQ(actual, (std::vector<int>{0, 1, 2, 3, 4}));
}

TEST(TopologicalSortKhan, SingleVertex) {
    int n = 1;
    std::vector<std::vector<int>> edges = {};
    auto actual = toplogicalSortKhan(n, edges);
    ASSERT_EQ(actual, (std::vector<int>{0}));
}

TEST(TopologicalSortKhan, TwoDisconnectedComponents) {
    // 0->1  and  2->3  — two independent chains
    int n = 4;
    std::vector<std::vector<int>> edges = {{0,1},{2,3}};
    auto actual = toplogicalSortKhan(n, edges);
    expectValidTopologicalOrderRaw(n, edges, actual);
}

TEST(TopologicalSortKhan, MultipleValidOrders) {
    // diamond: 0->1, 0->2, 1->3, 2->3
    int n = 4;
    std::vector<std::vector<int>> edges = {{0,1},{0,2},{1,3},{2,3}};
    auto actual = toplogicalSortKhan(n, edges);
    expectValidTopologicalOrderRaw(n, edges, actual);
}

TEST(TopologicalSortKhan, CycleReturnsEmpty) {
    // 0->1->2->0 creates a cycle — expect empty result
    int n = 3;
    std::vector<std::vector<int>> edges = {{0,1},{1,2},{2,0}};
    auto actual = toplogicalSortKhan(n, edges);
    ASSERT_TRUE(actual.empty()) << "Cycle should produce an empty result.";
}

TEST(TopologicalSortKhan, LargerDAG) {
    int n = 6;
    std::vector<std::vector<int>> edges = {{5,2},{5,0},{4,0},{4,1},{2,3},{3,1}};
    auto actual = toplogicalSortKhan(n, edges);
    expectValidTopologicalOrderRaw(n, edges, actual);
}

// ── Original Graph-based variant ──────────────────────────────────────────────

TEST(TopologicalSortKhan, BigGraph) {
    std::unordered_set<int> vertices={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    Graph graph(true);
    graph.addEdge(0,3);
    graph.addEdge(0,6);
    graph.addEdge(1,3);
    graph.addEdge(2,4);
    graph.addEdge(2,5);
    graph.addEdge(3,6);
    graph.addEdge(3,7);
    graph.addEdge(4,3);
    graph.addEdge(4,7);
    graph.addEdge(4,8);
    graph.addEdge(5,8);
    graph.addEdge(6,7);
    graph.addEdge(6,9);
    graph.addEdge(7,10);
    graph.addEdge(8,11);
    graph.addEdge(9,10);
    graph.addEdge(9,12);
    graph.addEdge(10,14);
    graph.addEdge(11,14);
    graph.addEdge(13,14);
    std::vector<int>actual= topologicalSortKhan(graph);

    expectValidTopologicalOrder(graph, actual);
}

