#pragma once

#include <string>
#include <vector>
#include "graph.hpp"

std::vector<int> topologicalSortKhan( const Graph & graph);
std::vector<int> toplogicalSortKhan(int n, std::vector<std::vector<int>>& edges);
