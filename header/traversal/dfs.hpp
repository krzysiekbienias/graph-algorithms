#pragma once

#include <string>
#include <vector>
#include "graph.hpp"

std::vector<Graph::Vertex> dfs(const Graph& graph, const Graph::Vertex& start);