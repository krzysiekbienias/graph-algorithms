#include <vector>
#include "traversal/count_city_clusters.hpp"


static void dfs(int city,const std::vector<std::vector<int>> &isConnected,std::vector<bool> &visited) {
    visited[city]=true;
    for (int nextCity = 0; nextCity < isConnected.size(); ++nextCity) {
        if (isConnected[city][nextCity]==1&& !visited[nextCity]) {
            dfs(nextCity,isConnected,visited);
        }
    }

}

int countCityClusters(const std::vector<std::vector<int>> &isConnected) {
    int nbOfCities=isConnected.size();
    std::vector<bool> visited(nbOfCities,false);
    int res=0;
    for (int city = 0; city < nbOfCities; ++city) {
        if (!visited[city]) {
            dfs(city,isConnected,visited);
            ++res;
        }
    }
    return res;

}
