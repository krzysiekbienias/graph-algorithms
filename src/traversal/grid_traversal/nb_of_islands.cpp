#include<vector>
#include "traversal/grid_traversal/is_within_bounds.hpp"

std::vector<std::pair<int,int>> directions={{-1,0},{0,-1},{0,1},{1,0}}; //U,L,R,D

static void dfs(int r,int c,std::vector<std::vector<int>>& grid) {
    grid[r][c]=-1;
    for (const auto &[dr,dc]:directions) {
        int newRow=dr+r;
        int newCol=dc+c;
        if (isWithinBounds(newRow,newCol,grid) && grid[newRow][newCol]==1) {
            dfs(newRow,newCol,grid);
        }
    }
}


int countIslands(std::vector<std::vector<int>>& grid) {
    int res=0;
    int rows=grid.size();
    int cols=grid[0].size();

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c]==1) {
                dfs(r,c, grid);
                res++;

            }
        }
    }
    return res;

}