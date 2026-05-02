#include "traversal/grid_traversal/nearest_exit_from_entrance.hpp"
#include <queue>
#include <utility>
#include "constants.hpp"
#include "traversal/grid_traversal/is_within_bounds.hpp"

static bool isOnEdge(int r, int c, int rows, int cols) {
    if (r == 0 || r == rows - 1 || c == 0 || c == cols - 1) {
        return true;
    }
    return false;
}

int nearestExit(std::vector<std::vector<char>>& maze, std::vector<int> entrance) {
    int res = 0;
    int nbOfRows = maze.size();
    int nbOfCols = maze[0].size();

    std::pair<int, int> startPoint = {entrance[0], entrance[1]};
    std::queue<std::pair<int, int>> q;
    // push entrance
    q.push(startPoint);
    maze[startPoint.first][startPoint.second] = '+';
    while (!q.empty()) {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; i++) {
            auto [row, col] = q.front();
            q.pop();
            for (const auto& [dr, dc] : directions) {
                int newRow = row + dr;
                int newCol = col + dc;
                if (isWithinBounds(newRow, newCol, maze) && maze[newRow][newCol] != '+') {
                    if (isOnEdge(newRow, newCol, nbOfRows, nbOfCols) && std::make_pair(newRow, newCol) != startPoint) {
                        return res + 1;
                    }
                    maze[newRow][newCol] = '+';
                    q.push({newRow, newCol});
                }
                
            }
        }
        res++;
    }
    return -1;
}
