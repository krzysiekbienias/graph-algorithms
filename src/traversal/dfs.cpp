#include <string>
#include <vector>

#include <unordered_set>
#include "graph.hpp"

std::vector<Graph::Vertex> dfs(const Graph& graph, const Graph::Vertex& start) {
    std::vector<Graph::Vertex> dfsOrder;

    if (!graph.containsVertex(start)) {
        return dfsOrder;
    }

    std::unordered_set<Graph::Vertex> visited;
    std::vector<Graph::Vertex> stack{start};

    while (!stack.empty()) {
        Graph::Vertex u = stack.back();
        stack.pop_back();

        if (!visited.insert(u).second) {
            continue;
        }

        dfsOrder.push_back(u);

        const auto& neighbors = graph.getNeighbors(u);
        for (auto it = neighbors.rbegin(); it != neighbors.rend(); ++it) {
            const Graph::Vertex& v = it->to;
            if (!visited.count(v)) {
                stack.push_back(v);
            }
        }
    }

    return dfsOrder;
}