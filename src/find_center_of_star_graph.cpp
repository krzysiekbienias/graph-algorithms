#include <string>
#include <vector>
#include <unordered_set>
#include "builders/adjacency_list_style.hpp"

int findCenter(const Graph& graph) {
    std::vector<Graph::Vertex> vecVertices;
    vecVertices=graph.getVertices();
    int nbOfVertices=vecVertices.size();
    for (Graph::Vertex vertex: vecVertices) {
        int nbOfNeighb=graph.getNeighbors(vertex).size();
        if (nbOfNeighb==nbOfVertices -1) {
            return int(vertex);
        }
    }
    return -1;

}
