#include <string>
#include <vector>
#include "traversal/grid_traversal/is_within_bounds.hpp"

static std::vector<std::pair<int,int>> directions={{-1,0},{1,0},{0,-1}, {0,1}};

static int dfs(std::vector<std::vector<int>>& matrix,std::vector<int>& res,int r,int c) {
    matrix[r][c]=-1;
    int riverSize=1;//bo juz stoimy ma jednej komorce rzeki skoro tu sie znalezlismy
    for (auto & [dr,dc]:directions){
        int newRow=r+dr;
        int newCol=c+dc;
        if (isWithinBounds(newRow, newCol, matrix) && matrix[newRow][newCol]==1) {
            riverSize+=dfs(matrix,res,newRow,newCol);
        }
    }
    return riverSize;
}

std::vector<int> riverSizes(std::vector<std::vector<int>>& matrix) {
    std::vector<int> res;
    int rowNb=matrix.size();
    int colNb=matrix[0].size();
    for (int r = 0; r < rowNb; ++r) {
        for (int c = 0; c < colNb; ++c) {
            int riverSize=dfs(matrix,res,r, c);
            res.push_back(riverSize);
        }
    }
    return res;

}


