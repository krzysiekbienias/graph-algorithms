#include <iostream>
#include <queue>
#include <unordered_set>
#include "builders/build_from_adjecency_list.hpp"
#include "builders/build_from_edge_list.hpp"
#include "display_box/basic_structure_display.hpp"
#include "display_box/pretty_display.hpp"
#include "graph.hpp"
#include "shortest_path/dijkstra.hpp"
#include "traversal/grid_traversal/is_within_bounds.hpp"

using namespace std;

int minimumPassesOfMatrix(vector<vector<int> > &matrix) {
    std::vector<std::pair<int, int> > directions = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}}; // U,L,R,D
    std::queue<pair<int, int> > q;
    int m = matrix.size();
    int n = matrix[0].size();
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] > 0) {
                q.push({i, j});
            }
        }
    }
    int passes = 0;
    while (!q.empty()) {
        int currentSize = q.size();

        bool convertedSomething = false;
        for (int k = 0; k < currentSize; ++k) {
            std::pair<int, int> tempLocation = q.front();
            q.pop();
            int temRow = tempLocation.first;
            int temCol = tempLocation.second;
            for (const auto &[dr,dc]: directions) {
                int newRow = dr + temRow;
                int newCol = dc + temCol;
                if (isWithinBounds(newRow, newCol, matrix) && matrix[newRow][newCol] < 0) {
                    matrix[newRow][newCol] *= -1;
                    q.push({newRow, newCol});
                    convertedSomething = true;
                }
            }
        }
        if (convertedSomething) passes++;
    }

    return passes;
}


int main() {
    vector<vector<int> > input = {
        {0, -1, -3, 2, 0},
        {1, -2, -5, -1, -3},
        {3, 0, 0, -4, -1}
    };;
    auto expected = 3;
    cout << minimumPassesOfMatrix(input);
}
