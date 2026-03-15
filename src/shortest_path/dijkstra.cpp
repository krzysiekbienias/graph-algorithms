#include <string>
#include <vector>
#include "graph.hpp"
#include "unordered_map"
#include "unordered_set"
#include "queue"



std::unordered_map<Graph::Vertex, int>
dijkstra(const Graph& graph, Graph::Vertex source) {
    int startingDistance = INT_MAX;

    std::unordered_map<Graph::Vertex, int> distanceMap;
    std::unordered_set<Graph::Vertex> visited;

    for (const auto& u : graph.getVertices()) {
        distanceMap[u] = startingDistance;
    }

    distanceMap[source] = 0;


    using State = std::pair<Graph::Weight, Graph::Vertex>;
    std::priority_queue<State> pq; //m=MinHeap
    pq.emplace(0, source);

    while (!pq.empty()) {
        auto item = pq.top();
        int dist = item.first;
        Graph::Vertex u = item.second;
        pq.pop();

        if (visited.count(u)) {
            continue;
        }
        visited.insert(u);

        const auto& neighbours = graph.getNeighbors(u);
        for (const auto& e : neighbours) {
            Graph::Vertex v = e.to;
            Graph::Weight w = e.weight;
            int cand = distanceMap[u] + w;

            if (cand < distanceMap[v]) {
                distanceMap[v] = cand;
                pq.emplace(cand, v);
            }
        }
    }

    return distanceMap;
}