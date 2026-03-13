#include <unordered_set>
#include <vector>
#include "graph.hpp"

/*
 * [[4,3,1],[3,2,4],[3],[4],[]]
*  	•	0 -> 4, 3, 1
    •	1 -> 3, 2, 4
    •	2 -> 3
    •	3 -> 4
    •	4 -> (no neighbors)
 * note that we assume vertices are 0,1,... like because this is the way how we treat indices of the list
 */

Graph buildGraphFromAdjList(
    const std::vector<std::vector<Graph::Vertex>>& adjList,
    bool directed = true) {
    Graph g(directed);

    for (Graph::Vertex v = 0; v < static_cast<Graph::Vertex>(adjList.size()); ++v) {
        g.addVertex(v);
    }

    for (Graph::Vertex from = 0; from < static_cast<Graph::Vertex>(adjList.size()); ++from) {
        for (const Graph::Vertex& to : adjList[from]) {
            if (to < 0 || to >= static_cast<Graph::Vertex>(adjList.size())) {
                throw std::out_of_range("Neighbor vertex index out of range.");
            }

            g.addEdge(from, to);
        }
    }

    return g;
}

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
    bool directed = true) {
    Graph g(directed);

    for (int u = 0; u < static_cast<int>(adjList.size()); ++u) {
        g.addVertex(u);
    }

    for (int u = 0; u < static_cast<int>(adjList.size()); ++u) {
        for (const auto& edge : adjList[u]) {
            Graph::Vertex v = edge[0];
            Graph::Weight w = edge[1];
            g.addEdge(u, v, w);
        }
    }

    return g;
}
