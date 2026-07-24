#include <string>
#include <vector>
#include <queue>

bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites) {
std::vector<std::vector<int>>  graph(numCourses);
std::vector<int> inDegree(numCourses,0);
//create graph represented by adjList and inDegree vector
for (const auto & edge:prerequisites) {
    int from =edge[0];
    int to =edge[1];

    graph[from].push_back(to);
    inDegree[to]++;
}
//ready means that it in this particular moment you may pick up task ,course and so on
std::queue<int> readyQueue;
for (int i=0;i<numCourses;++i) {
    if (inDegree[i]==0) {
        readyQueue.push(i);
    }
}
std::vector<int> topoOrder;
while (!readyQueue.empty()) {
    int curr=readyQueue.front();
    readyQueue.pop();
    topoOrder.push_back(curr);
    
    std::vector<int> &neighbpours=graph[curr];
    for (int neighbour:neighbpours) {
        inDegree[neighbour]--;
        if (inDegree[neighbour]==0) {
            readyQueue.push(neighbour);
        }
    }
    
}
//cycle detection
if (numCourses!=topoOrder.size()) {
    return false;
}
return true;
}