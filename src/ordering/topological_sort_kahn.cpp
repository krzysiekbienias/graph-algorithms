#include <graph.hpp>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<int> topologicalSortKhan(const Graph& graph) {
    using GV = Graph::Vertex;
    using GE = Graph::Edge;
    std::unordered_map<GV, int> inDegree;
    std::vector<GV> vertices = graph.getVertices();
    for (GV u : vertices) {
        inDegree[u] = 0;
    }
    for (GV v : vertices) {
        auto neighbours = graph.getNeighbors(v);
        for (const auto& edge : neighbours) {
            GV to = edge.to;
            inDegree[to]++;
        }
    }
    std::queue<GV> readyQueue;
    std::vector<GV> topoOrder;
    for (const auto [v, deq] : inDegree) {
        if (deq == 0) {
            readyQueue.push(v);
        }
    }
    while (!readyQueue.empty()) {
        GV v = readyQueue.front();
        readyQueue.pop();
        topoOrder.push_back(v);
        std::vector<GE> neighbours = graph.getNeighbors(v);
        for (const auto& edge : neighbours) {
            GV to = edge.to;
            inDegree[to]--;
            if (inDegree[to]== 0) {
                readyQueue.push(to);
            }
        }
    }
    if (topoOrder.size() != vertices.size())
        return {};  // cycle soe there is no topological order

    return topoOrder;
}
