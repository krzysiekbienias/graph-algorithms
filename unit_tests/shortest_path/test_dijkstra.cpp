#include <gtest/gtest.h>
#include "graph.hpp"
#include <unordered_set>
#include "shortest_path/dijkstra.hpp"


TEST(Dijkstra, SimpleGraph) {
    auto graph=Graph(true);
    std::unordered_set<int> vertexes={0,1,2,3,4};
    for (int vertex:vertexes) {
        graph.addVertex(vertex);
    }

    graph.addEdge(0,1,9);
    graph.addEdge(0,2,6);
    graph.addEdge(0,3,5);
    graph.addEdge(1,3,2);
    graph.addEdge(2,4,1);
    graph.addEdge(3,4,2);

    dijkstra(graph,0);

}
