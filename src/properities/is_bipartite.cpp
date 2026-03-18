#include <string>
#include <vector>
#include <graph.hpp>

bool isBipartite(const Graph& graph) {
    using Vertex=Graph::Vertex;
    std::unordered_map<int,int> colors;
    //color[v]=-1 unvisited
    for (Vertex v:graph.getVertices()) {
        colors[v]=-1;
    }
    for (const Vertex&start:graph.getVertices()) {
        if (colors[start]!=-1) {
            continue;
        }
        std::queue<Vertex> q;
        q.push(start);
        colors[start]=0;
        while (!q.empty()) {
            Vertex u=q.front();
            q.pop();
            std::vector<Graph::Edge> uNeighbours=graph.getNeighbors(u);
            for (const auto & edge:uNeighbours) {
                //u <--> v1,v2,v3 vi are neighbours
                Vertex v=edge.to;
                if (colors[v]==-1) {
                    colors[v]=1-colors[u];
                    q.push(v);
                }
                else if (colors[u]==colors[v]) {
                    return false;
                }

            }

        }
    }
    return true;

}