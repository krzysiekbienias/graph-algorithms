#include <string>
#include <vector>
#include "graph.hpp"


int maximalNetworkRank(int n,const  std::vector<std::vector<int>> &roads) {
    std::vector<std::vector<int>> graph(n);
    std::vector<std::vector<bool>> connectedMatrix(n,std::vector<bool>(n,false));
    for (const auto & item:roads)
    {
        int from = item[0];
        int to = item[1];
        graph[from].push_back(to);
        graph[to].push_back(from);
        connectedMatrix[from][to]=true;
        connectedMatrix[to][from]=true;
    }
    int bestRank=0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = i+1; j < n; ++j)
        {
            int currentRank=graph[i].size()+graph[j].size();
            if (connectedMatrix[i][j])
            {
                currentRank--;
            }
            bestRank=std::max(currentRank,bestRank);
        }

    }
    return bestRank;
}
