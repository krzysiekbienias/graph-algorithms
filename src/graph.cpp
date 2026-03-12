#include "graph.hpp"

#include <string>
#include <vector>


Graph::Graph(bool directed) :m_directed(directed){};

bool Graph::containsVertex(const Vertex& v) const {
    return m_adjList.contains(v);
}

size_t Graph::vertexCount() const {
    return m_adjList.size();
}



bool Graph::addVertex(const Vertex &v) {
    return m_adjList.try_emplace(v, std::vector<Edge>{}).second;
}

void Graph::addEdge(const Vertex &u, const Vertex &v, Weight weight) {
    addVertex(u);
    addVertex(v);
    m_adjList[u].push_back(Edge{v, weight});
    //it handles automatic connection in both directions
    if (!m_directed)
        m_adjList[v].push_back(Edge{u, weight});
}

const std::vector<Graph::Edge> &Graph::getNeighbors(const Vertex &v) const {
    static const std::vector<Edge> neighbors; //dummy vector of edges to hold neighbors.
    auto it = m_adjList.find(v);
    return (it == m_adjList.end()) ? neighbors : it->second;
    //it->second is vector as well!
}

std::vector<Graph::Vertex> Graph::getVertices() const {
    std::vector<Vertex> vertices;
    vertices.reserve(m_adjList.size());
    for (const auto &[k,_]: m_adjList) {
        vertices.push_back(k);
    }
    return vertices;
}