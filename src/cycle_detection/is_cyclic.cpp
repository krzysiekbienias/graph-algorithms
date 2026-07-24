#include <vector>

#include "cycle_detection/is_cyclic.hpp"

namespace {

enum class Color {
    White,  // not visited yet
    Gray,   // on the current recursion stack
    Black   // fully processed
};

// returns true if a cycle is reachable from u
bool dfs(int u, const std::vector<std::vector<int>>& adj, std::vector<Color>& colors) {
    colors[u]=Color::Gray; //paint on grey
    int n= adj.size();
    std::vector<int> neigh;
    
    neigh=adj[u];
    for (const auto& v : neigh) {
        if (colors[v]==Color::Gray){
            return true;//we have found a cycle
        }
        if (colors[v]==Color::White){
           if(dfs(v,adj,colors))
            return true;//podaj meldunek

        }
    }
    colors[u]=Color::Black;
    return false;
}

}  // namespace

bool isCyclic(std::vector<std::vector<int>>& adj) {
    int n= adj.size();
    std::vector<Color> colors (n,Color::White);
    for (int u = 0; u < n; u++) {
        if (colors[u]!=Color::White){
            continue;//dfs only launch on white node
        }    
        if(dfs(u, adj, colors)){
            return true; //only if dfs returns true return true
        }
    }
    return false;
}
