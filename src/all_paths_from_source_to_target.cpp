#include <string>
#include <vector>
#include "graph.hpp"

static void dfsBacktracking(
    const Graph& graph,
    Graph::Vertex current,
    Graph::Vertex target,
    std::vector<Graph::Vertex>& currentPath,
    std::vector<std::vector<Graph::Vertex>>& allPaths) {
    using GV = Graph::Vertex;
    using GE = Graph::Edge;
    if (current == target) {
        allPaths.emplace_back(currentPath);
        return;
    }
    std::vector<GE> neighbours = graph.getNeighbors(current);
    for (const auto& edge : neighbours) {
        GV next = edge.to;
        currentPath.push_back(next);
        dfsBacktracking(graph, next, target, currentPath, allPaths);
        currentPath.pop_back();
    }
}

std::vector<std::vector<int>> allPathsSourceTarget(const Graph& graph) {
    // we assume that the graph is DAG.
    using GV = Graph::Vertex;
    using GE = Graph::Edge;

    GV start = 0;
    int target = graph.vertexCount() - 1;
    std::vector<std::vector<GV>> allPaths;
    std::vector<GV> currentPath{0};
    dfsBacktracking(graph, start, target, currentPath, allPaths);

    return allPaths;
}




/* Below more friendly interview oriented,
 *
 *
 *
 */

static void dfs(int currentNode,
            int target,
            std::vector<std::vector<int>> &graph,
            std::vector<int>& currPath,
            std::vector<std::vector<int>> &res) {
    //add cuurent Node to current Path
    currPath.push_back(currentNode);
    if (currentNode==target) {
        res.push_back(currPath);
    }
    else {
        //explore
        for (int neigh:graph[currentNode]) {
            dfs(neigh,target,graph,currPath,res);
        }
    }
    currPath.pop_back();

}


std::vector<std::vector<int>> allPathsSourceTarget(std::vector<std::vector<int>>& graph) {
    std::vector<std::vector<int>> result;
    std::vector<int> currPath;
    int n=graph.size();

    int target=n-1;

    dfs(0,target,graph,currPath,result);

    return result;
}