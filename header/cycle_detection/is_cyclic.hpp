#pragma once

#include <vector>

// GfG: Detect Cycle in a Directed Graph
// adj[u] = list of nodes v such that there is an edge u -> v
// vertices are assumed to be 0..n-1
bool isCyclic(std::vector<std::vector<int>>& adj);
