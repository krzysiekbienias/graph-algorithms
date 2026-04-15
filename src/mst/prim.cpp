#include <queue>
#include <string>
#include <vector>

std::vector<std::vector<std::vector<int>>> primsAlgorithm(std::vector<std::vector<std::vector<int>>> edges) {
    int n=edges.size();
    std::vector<std::vector<std::vector<int>>> mst(n);

    //tracker
    std::vector<bool> visited(n,false);

    //weight, from, to
    using HeapEntry =std::tuple<int,int,int>;
    std::priority_queue<HeapEntry,std::vector<HeapEntry>,std::greater<HeapEntry>> pq;
    for (int start = 0; start < n; ++start) {
        if (visited[start]) {
            continue;
        }
        pq.emplace(0,-1,start);
        while (!pq.empty()) {
            auto item=pq.top();
            int weight=get<0>(item);
            int from=get<1>(item);
            int to=get<2>(item);
            pq.pop();
            if (visited[to]) {
                continue;
            }
            visited[to]=true;
            //skip fake starting edge
            if (from!=-1) {
                mst[from].push_back({to,weight});
                mst[to].push_back({from,weight});
            }
            for (const auto& neighbor:edges[to]) {
                int next=neighbor[0];
                int nextWeight=neighbor[1];

                if (!visited[next]) {
                    pq.emplace(nextWeight,to,next);
                }
            }
        }
    }
        return mst;
}
