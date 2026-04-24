#pragma once

#include <string>
#include <vector>
#include "graph.hpp"

std::vector<Graph::Vertex> dfs(const Graph& graph, const Graph::Vertex& start);
std::vector<int> dfs(const std::vector<std::vector<int>>& graph, int start);