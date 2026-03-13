#include <string>
#include <vector>
#include "graph.hpp"

static void dfsBacktracking(
    const Graph& graph,
    Graph::Vertex current,
    Graph::Vertex target,
    std::vector<Graph::Vertex>& currentPath,
    std::vector<std::vector<Graph::Vertex>>& allPaths) {
    using GV = Graph::Vertex;
    using GE = Graph::Edge;
    if (current == target) {
        allPaths.emplace_back(currentPath);
        return;
    }
    std::vector<GE> neighbours = graph.getNeighbors(current);
    for (const auto& edge : neighbours) {
        GV next = edge.to;
        currentPath.push_back(next);
        dfsBacktracking(graph, next, target, currentPath, allPaths);
        currentPath.pop_back();
    }
}

std::vector<std::vector<int>> allPathsSourceTarget(const Graph& graph) {
    // we assume that the graph is DAG.
    using GV = Graph::Vertex;
    using GE = Graph::Edge;

    GV start = 0;
    int target = graph.nbOfVertices() - 1;
    std::vector<std::vector<GV>> allPaths;
    std::vector<GV> currentPath{0};
    dfsBacktracking(graph, start, target, currentPath, allPaths);

    return allPaths;
}


std::vector<std::vector<int>> allPathsSourceTarget(const std::vector<std::vector<int>>& graph) {
    return {{}};
}
