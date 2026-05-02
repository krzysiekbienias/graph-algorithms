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

//for topological order we usually get edges

std::vector<int> toplogicalSortKhan(int n,std::vector<std::vector<int>>& edges) {
    std::vector<std::vector<int>>  graph(n);
    std::vector<int> inDegree(n,0);
    //create graph represented by adjList and inDegree vector
    for (const auto & edge:edges) {
        int from =edge[0];
        int to =edge[1];

        graph[from].push_back(to);
        inDegree[to]++;
    }
    //ready means that it in this particular moment you may pick up task ,course and so on
    std::queue<int> readyQueue;
    for (int i=0;i<n;++i) {
        if (inDegree[i]==0) {
            readyQueue.push(i);
        }
    }
    std::vector<int> topoOrder;
    while (!readyQueue.empty()) {
        int curr=readyQueue.front();
        readyQueue.pop();
        topoOrder.push_back(curr);

        std::vector<int> &neighbpours=graph[curr];
        for (int neighbour:neighbpours) {
            inDegree[neighbour]--;
            if (inDegree[neighbour]==0) {
                readyQueue.push(neighbour);
            }
        }

    }
    //cycle detection
    if (n!=topoOrder.size()) {
        return {};
    }
    return topoOrder;
}