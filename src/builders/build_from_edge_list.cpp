#include <unordered_set>
#include <vector>
#include "graph.hpp"
/*
  {
    {0, 1, 4},
    {0, 2, 7},
    {1, 3, 2}
  }

    •   0 -> 1 with weight 4
    •	0 -> 2 with weight 7
    •	1 -> 3 with weight 2

 */

Graph buildGraphFromWeightedEdgeList(
    int n,
    const std::vector<std::vector<int>>& edgeList,
    bool directed = true) {
    Graph g(directed);

    for (int v = 0; v < n; ++v) {
        g.addVertex(v);
    }

    for (const auto& edge : edgeList) {
        Graph::Vertex from = edge[0];
        Graph::Vertex to = edge[1];
        Graph::Weight weight = edge[2];

        g.addEdge(from, to, weight);
    }

    return g;
}

/*
 * edges = [[1,2],[2,3],[4,2]]
 * but you need to pass also set of verices explicite.
 */
Graph buildGraphFromEdgeList(
    const std::unordered_set<Graph::Vertex>& vertices,
    const std::vector<std::vector<int>>& edgeList,
    bool directed = true) {
    Graph g(directed);

    // add vertices
    for (Graph::Vertex v : vertices) {
        g.addVertex(v);
    }

    // add edges
    for (const auto& edge : edgeList) {
        if (edge.size() != 2) {
            throw std::invalid_argument(
                "Each edge must contain exactly [from, to]");
        }

        Graph::Vertex from = edge[0];
        Graph::Vertex to = edge[1];

        if (!vertices.contains(from) || !vertices.contains(to)) {
            throw std::invalid_argument(
                "Edge references vertex not present in vertex set");
        }

        g.addEdge(from, to);
    }

    return g;
}