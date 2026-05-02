
#include <vector>
#include "traversal/grid_traversal/is_within_bounds.hpp"
#include <queue>




static std::vector<std::pair<int, int>> directions = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};  // U,L,R,D

int getFood(std::vector<std::vector<char>>& grid) {
    std::pair<int, int> startPoint = {-1, -1};
    int r = grid.size();
    int c = grid[0].size();
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (grid[i][j] == '*') {
                startPoint = {i, j};
                break;
            }
        }
        if (startPoint.first != -1) {
            break;
        }
    }
    std::queue<std::pair<int, int>> q;
    q.push(startPoint);
    grid[startPoint.first][startPoint.second] = 'X';  // mark visited
    int steps = 0;
    while (!q.empty()) {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; ++i) {
            auto [row, col] = q.front();
            int debugRow=row;
            int debugCol=col;
            q.pop();
            if (grid[row][col] == '#') {
                return steps;
            }
            for (const auto& [dr, dc] : directions) {
                int newRow = row + dr;
                int newCol = col + dc;
                if (isWithinBounds(newRow, newCol, grid) && grid[newRow][newCol] != 'X') {
                    if (grid[newRow][newCol] == '#') {
                        return steps + 1;
                    }
                    if (grid[newRow][newCol] == 'O') {
                        q.push({newRow, newCol});
                        grid[newRow][newCol] = 'X';  // mark visited
                    }
                }
            }
        }
        steps++;
    }

    return -1;
}
