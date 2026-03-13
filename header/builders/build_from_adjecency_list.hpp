#pragma once

#include <vector>
#include "graph.hpp"

/*
 * [[4,3,1],[3,2,4], [3], [4],[]]
*  	•	0 -> 4, 3, 1
    •	1 -> 3, 2, 4
    •	2 -> 3
    •	3 -> 4
    •	4 -> (no neighbors)
 * note that we assume vertices are 0,1,... like because this is the way how we treat indices of the list
 */

Graph buildGraphFromAdjList(
    const std::vector<std::vector<Graph::Vertex>>& adjList,
    bool directed = true);

/*
   [   [
       [1, 7]
       ],
       [
           [2, 6],
           [3, 20],
           [4, 3]
       ],
       [
           [3, 14]
       ],
       [
           [4, 2]
       ],
       [],
       []
   ]
    */

Graph buildGraphFromWeightedAdjList(

    const std::vector<std::vector<std::vector<int>>>& adjList,
    bool directed = true);
