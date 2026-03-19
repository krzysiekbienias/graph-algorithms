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

std::unordered_map<int,int> dijkstra(const std::vector<std::vector<int>>& graph,int source) {
    std::unordered_map<int,int> distMap;
    int n=graph.size();
    //build adjacent list
    std::vector<std::vector<std::pair<int,int>>> adj(n);
    for (const auto & item:graph) {
        int from=item[0];
        int to=item[1];
        int weight=item[2];
        adj[from].push_back({to,weight});
        adj[to].push_back({from,weight}); //because bidirectional
    }
    int inf=INT_MAX;
    for (int i =0;i<adj.size();i++) {
        distMap[i]=inf;
    }
    distMap[source]=0;
    std::vector<bool> visited(n,false);
    using HeapEntry=std::pair<int,int> ;//<weight, to>
    std::priority_queue<HeapEntry,std::vector<HeapEntry>,std::greater<HeapEntry>> pq;
    pq.emplace(0,source);
    while (!pq.empty()) {
        auto [currentWeight,from]=pq.top(); // tu nie moze byc referencji WAZNE
        pq.pop();
        if (visited[from]) {
            continue;
        }
        visited[from]=true; //or visited.insert(from) if we decide on set
        for (const auto & [to,weight]:adj[from])
        {
            if (!visited[to] && currentWeight+weight<distMap[to]) {
                distMap[to]=currentWeight+weight;
                pq.push({distMap[to],to});
            }
        }
    }
    return distMap;
}



std::vector<int> dijkstra(int n,const std::vector<std::vector<int>>& graph,int source) {

    //build adjacent list
    std::vector<std::vector<std::pair<int,int>>> adj(n);
    for (const auto & item:graph) {
        int from=item[0];
        int to=item[1];
        int weight=item[2];
        adj[from].push_back({to,weight});
        adj[to].push_back({from,weight}); //because bidirectional
    }

    std::vector<int> dist(n);
    int inf=INT_MAX;
    for (int i =0;i<adj.size();i++) {
        dist[i]=inf;
    }
    dist[source]=0;
    std::vector<bool> visited(n,false);
    using HeapEntry=std::pair<int,int> ;//<weight, to>
    std::priority_queue<HeapEntry,std::vector<HeapEntry>,std::greater<HeapEntry>> pq;
    pq.emplace(0,source);
    while (!pq.empty()) {
        auto [currentWeight,from]=pq.top(); // tu nie moze byc referencji WAZNE
        pq.pop();
        if (visited[from]) {
            continue;
        }
        visited[from]=true; //or visited.insert(from) if we decide on set
        for (const auto & [to,weight]:adj[from])
        {
            if (!visited[to] && currentWeight+weight<dist[to]) {
                dist[to]=currentWeight+weight;
                pq.push({dist[to],to});
            }
        }
    }
    return dist;
}