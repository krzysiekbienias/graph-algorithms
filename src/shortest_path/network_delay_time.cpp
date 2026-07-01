#include <string>
#include <vector>
# include "shortest_path/dijkstra.hpp"



static std::vector<int> dijkstraOneDirectional(int n,const std::vector<std::vector<int>>& graph,int source) {

    //build adjacent list
    std::vector<std::vector<std::pair<int,int>>> adj(n+1);
    for (const auto & item:graph) {
        int from=item[0];
        int to=item[1];
        int weight=item[2];
        adj[from].push_back({to,weight});
    }

    std::vector<int> dist(n+1);
    int inf=INT_MAX;
    for (int i =0;i<adj.size();i++) {
        dist[i]=inf;
    }
    dist[source]=0;
    std::vector<bool> visited(n+1,false);
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


int networkDelayTime(std::vector<std::vector<int>>& times, int n, int k) {
    std::vector<int> shortestPath= dijkstraOneDirectional(n,times,k);
    int maxTime=0;
    for (int i = 1; i <=n; ++i) {
        if (shortestPath[i]==INT_MAX) return -1;
        if (maxTime<shortestPath[i]) {
            maxTime=shortestPath[i];
        }
    }
    return maxTime;
}

