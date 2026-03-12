#pragma once


#include <string>
#include <vector>
#include <unordered_map>
#include <ostream>



class Graph {
public:
    using Vertex = int;
    using Weight = int;

    struct Edge {
        int to;
        int weight;

        friend std::ostream &operator<<(std::ostream &os, const Edge &e) {
            return os << "--(" << e.weight << ")-->" << e.to;
        }
    };


    static constexpr int INF =1'000'000'000;


    explicit Graph(bool directed = true);

    bool addVertex(const Vertex &v);

    bool containsVertex(const Vertex& v) const;

    void addEdge(const Vertex &u, const Vertex &v, Weight w = 1);

    std::vector<Vertex> getVertices() const;

    const std::vector<Edge> &getNeighbors(const Vertex &v) const;

    size_t vertexCount() const;


private:
    bool m_directed{true};
    std::unordered_map<Vertex, std::vector<Edge>> m_adjList;
};