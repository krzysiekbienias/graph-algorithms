#pragma once

#include <unordered_set>
#include <vector>
#include "graph.hpp"

/*
  {
    {0, 1, 4},
    {0, 2, 7},
    {1, 3, 2}
  }

    •   0 -> 1 with weight 4
    •	0 -> 2 with weight 7
    •	1 -> 3 with weight 2

 */

Graph buildGraphFromWeightedEdgeList(
    int n,
    const std::vector<std::vector<int>>& edgeList,
    bool directed = true);

/*
 * edges = [[1,2],[2,3],[4,2]]
 * but you need to pass also set of verices explicite.
 */
Graph buildGraphFromEdgeList(
    const std::unordered_set<Graph::Vertex>& vertices,
    const std::vector<std::vector<int>>& edgeList,
    bool directed = true);
