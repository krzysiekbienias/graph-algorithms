#include <string>
#include <vector>
#include <unordered_set>

#include "graph.hpp"

std::vector<Graph::Vertex> bfs(const Graph& graph, const Graph::Vertex& start) {
    std::vector<Graph::Vertex> bfsOrder;

    if (!graph.containsVertex(start)) {
        return bfsOrder;
    }

    std::unordered_set<Graph::Vertex> visited;
    std::queue<Graph::Vertex> queue;

    visited.insert(start);
    queue.push(start);

    while (!queue.empty()) {
        Graph::Vertex u = queue.front();
        queue.pop();

        bfsOrder.push_back(u);

        const auto& neighbors = graph.getNeighbors(u);
        for (const auto& edge : neighbors) {
            const Graph::Vertex& v = edge.to;
            if (!visited.count(v)) {
                visited.insert(v);
                queue.push(v);
            }
        }
    }

    return bfsOrder;
}