#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "graph.hpp"
#include "constants.hpp"


std::unordered_map<Graph::Vertex, int> dijkstra(const Graph& graph, Graph::Vertex source);

std::vector<int> dijkstra(int n,const std::vector<std::vector<int>>& graph,int source);

std::unordered_map<int,int> dijkstra(const std::vector<std::vector<int>>& graph,int source);