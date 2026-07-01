#include <string>
#include <vector>
#include <queue>


static std::vector<int> dijkstraBiDirectional(int n,const std::vector<std::vector<int>>& graph,int source) {

    //build adjacent list
    std::vector<std::vector<std::pair<int,int>>> adj(n+1);
    for (const auto & item:graph) {
        int from=item[0];
        int to=item[1];
        int weight=item[2];
        adj[from].push_back({to,weight});
        adj[to].push_back({from,weight});
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

static long long calculateCost(int dist, int price, int k) {
    return dist+price+dist*k;
}

std::vector<long long> minCost(int n, std::vector<std::vector<int>>& roads, std::vector<int>& appleCost, int k) {
    std::vector<long long> res;
    for (int i = 1; i <= n; ++i) {
        std::vector<int> distPerSource=dijkstraBiDirectional(n,roads,i);
        long long minPerSource=INT_MAX;
        for (int j = 1; j < distPerSource.size(); ++i) {
            if (distPerSource[j]==minPerSource) continue;
            long long currentCost=calculateCost(distPerSource[j],appleCost[j-1],k);
            minPerSource=std::min(minPerSource,currentCost);

        }
        res.push_back(minPerSource);
    }

}