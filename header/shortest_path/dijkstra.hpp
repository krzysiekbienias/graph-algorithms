#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "graph.hpp"
#include "constants.hpp"


std::unordered_map<Graph::Vertex, int> dijkstra(const Graph& graph, Graph::Vertex source);