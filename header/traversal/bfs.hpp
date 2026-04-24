#pragma once
#include "graph.hpp"
#include <string>
#include <vector>

std::vector<Graph::Vertex> bfs(const Graph& graph, const Graph::Vertex& start);