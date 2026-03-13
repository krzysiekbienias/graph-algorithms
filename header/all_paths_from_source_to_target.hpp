#pragma once

#include <string>
#include <vector>
#include "graph.hpp"

std::vector<std::vector<int>> allPathsSourceTarget(const Graph& graph);

//we might use overloading function to also solve this problem without reference to api

std::vector<std::vector<int>> allPathsSourceTarget(const std::vector<std::vector<int>> & graph);
