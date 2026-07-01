#include<vector>
#include <queue>
#include <constants.hpp>
#include "traversal/grid_traversal/is_within_bounds.hpp"

static void dfs(std::vector<std::vector<int>>& grid,int r, int c,std::queue<std::pair<int,int>> &q) {
    grid[r][c]=-1;
    q.push({r,c});
    for (auto & [dr,dc]:directions) {
        dr=dr;
        dc=dc;
        int newRow=r+dr;
        int newCol=c+dc;
        if (isWithinBounds(r,c,grid) && grid[newRow][newCol]==1) {
            dfs(grid,newRow,newCol,q);
        }
    }
}

int shortestBridge(std::vector<std::vector<int>>& grid) {
    int n=grid.size();
    bool foundFirstIsland=false;
    std::queue<std::pair<int,int>> q;

    for (int r = 0; r < n && !foundFirstIsland; ++r) {
        for (int c = 0; c < n && !foundFirstIsland; ++c) {
            if (grid[r][c]==1) {
                dfs(grid,r,c,q);
                foundFirstIsland=true;
            }

        }
    }

    while (!q.empty()) {
        // bfs logic with size !

    }
    return 0;

}