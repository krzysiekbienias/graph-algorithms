#include <vector>
#include <queue>
#include <constants.hpp>
#include <traversal/grid_traversal/is_within_bounds.hpp>

std::vector<std::vector<int>> nearestDistanceTo0(std::vector<std::vector<int>> &mat) {
    int r=mat.size();
    int c=mat[0].size();
    std::queue<std::pair<int,int>> q;
    //pre preparing container fo find distance
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (mat[i][j]==0) {
                q.push({i,j});
            }
            else {
                mat[i][j]=-1;
            }
        }
    }
    while (!q.empty()) {
        auto [row,col] =q.front(); //queue from begining
        int debugRow=row;
        int debugCol=col;
        q.pop();
        for (const auto & [dr,dc]:directions) {
            int newRow=row+dr;
            int newCol=col+dc;
            if ( isWithinBounds(newRow,newCol,mat) && mat[newRow][newCol]==-1) {
                mat[newRow][newCol]=mat[row][col]+1;
                q.push({newRow,newCol});

            }
        }

    }
    return mat;
}
