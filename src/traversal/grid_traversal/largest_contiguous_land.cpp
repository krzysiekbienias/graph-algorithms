#include <vector>
#include "constants.hpp"
#include "traversal/grid_traversal/is_within_bounds.hpp"

static int dfs(int r,int c,std::vector<std::vector<int>>& grid) {
    grid[r][c]=-1;
    int contiguousArea=1;
    for (const auto &[dr,dc]:directions) {
        int newRow=dr+r;
        int newCol=dc+c;
        if (isWithinBounds(newRow,newCol,grid) && grid[newRow][newCol]==1) {

            contiguousArea+=dfs(newRow,newCol,grid);
        }
    }
    return  contiguousArea;
}

int maxAreaOfIsland(std::vector<std::vector<int>> &grid) {
    int maxArea=0;
    int rows=grid.size();
    int cols=grid[0].size();
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c]==1) {
                int localArea=dfs(r,c,grid);
                maxArea=std::max(maxArea,localArea);
            }
        }
    }
    return maxArea;
}