#include <string>
#include <vector>
#include "shortest_path/dijkstra.hpp"



int findTheCity(int n, std::vector<std::vector<int>> &edges, int distanceThreshold) {
    int bestCity=-1;
    int minReachable=INT_MAX;
    for (int i=0;i<n;i++){
        std::vector<int>dist= dijkstra(n,edges,i);
        int nbOfReachable=0;
        for (int j=0;j<n;j++){
            if(i!=j && dist[j]<=distanceThreshold){
                nbOfReachable++;
            }
        }
        if ((nbOfReachable<minReachable) || (nbOfReachable==minReachable && bestCity<i)) {
            minReachable=nbOfReachable;
            bestCity=i;
        }

    }

    return bestCity;
}
