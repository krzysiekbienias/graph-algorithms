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


//BFS for graph given by square matrix with n dimension.

std::vector<int> bfsMatrix(const std::vector<std::vector<int>> & graph, int start) {
    int n=graph.size();
    std::vector<int> bfsOrder;

    std::vector<bool> visited(n,false);
    std::queue<int> q;

    q.push(start);
    visited[start]=true;

    while (!q.empty()) {
        int u=q.front();
        q.pop();
        bfsOrder.push_back(u);
        for (int v = 0; v < n; ++v) {
            //graph[u][v] =1 there is connection
            if (graph[u][v]==1 && !visited[v]) {
                visited[v]=true;
                q.push(v);
            }
        }
    }
    return bfsOrder;
}

//vertexes are 0, 1,2, ..., n-1
std::vector<int> bfsAdjList(const std::vector<std::vector<int>> & graph,int start) {
    int n=graph.size();
    std::vector<int> bfsOrder;


    if (start<0 || start>=n) {
        return bfsOrder;
    }
    std::vector<bool> visited(n,false);
    std::queue<int> q;

    q.push(start);
    visited[start]=true;

    while (!q.empty()) {
        int u=q.front();
        bfsOrder.push_back(u);
        q.pop();

        const auto& neighbours=graph[u];
        for ( int v:neighbours) {
            if (!visited[v]) {
                visited[v]=true;
                q.push(v);
            }
        }
    }
    return bfsOrder;
}