#include <string>
#include <vector>

int static dfs( int u, const std::vector<std::vector<int>> &graph, const std::vector<int>& informTime) {
    int maxTime=0;

    for (int v: graph[u]) {
        maxTime=std::max(maxTime,dfs(v,graph,informTime));
    }
    return maxTime+informTime[u];
}

int numOfMinutes(int n, int headID, std::vector<int>& manager, std::vector<int>& informTime) {
    //build adj list

    //indexes are employees here.

    std::vector<std::vector<int>> graph(n);
    for (int i = 0; i < n; ++i) {
        if (manager[i]!=-1){//guard to not have -1 as index
            graph[manager[i]].push_back(i);
        }
    }
    return dfs(headID,graph,informTime);

}