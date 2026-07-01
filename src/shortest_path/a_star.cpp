#include "traversal/grid_traversal/is_within_bounds.hpp"
#include "shortest_path/a_star.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <constants.hpp>

int manhatanMetric(const Position &p1, const Position &p2){
    return abs(p1.row-p2.row)+abs(p1.col-p2.col); 
}


std::vector<std::vector<int>> aStarAlgorithm(int startRow, int startCol, int endRow, int endCol, std::vector<std::vector<int>> graph){
    Position start={startRow,startCol};
    Position end ={endRow,endCol};
        
    using HeapEntry = std::pair<int, Position>;

    struct HeapCompare {
        bool operator()(const HeapEntry& a, const HeapEntry& b) const {
            return a.first > b.first;
        }
    };

    std::priority_queue<HeapEntry, std::vector<HeapEntry>, HeapCompare> pq;
    
    std::unordered_set<Position,PositionHash> visited;
    std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    std::unordered_map<Position, int,PositionHash> gScore;
    std::unordered_map<Position, Position,PositionHash> parent;
    
    int g=0;
    gScore[start]=0;
    int f=manhatanMetric(start, end);
    pq.emplace(f,start);

    while(!pq.empty()){
        auto [f,current]=pq.top();
        pq.pop();
        if (visited.count(current)){
            continue;//already cheched jump to nother location
        }
        visited.insert(current);

        if(current==end){
            std::vector<std::vector<int>> path;
            Position node=end; //temp node set at the end becasue we traverece from end 
            while (node!=start){
                path.push_back({node.row,node.col});
                node=parent[node];
            }
            //at the end and start as well
            path.push_back({start.row,start.col});

            std::reverse(path.begin(),path.end());
            return path;
        }
        for (const auto& [dr, dc] : directions) {
            int newRow=current.row+dr;
            int newCol=current.col+dc;
            if (!isWithinBounds(newRow,newCol,graph)) {
                continue;
            }
            if (graph[newRow][newCol]==1) {
                continue;
            }
            Position neighbor={newRow,newCol};

            int tentativeG=gScore[current]+1;

            if(!gScore.count(neighbor) || tentativeG<gScore[neighbor]){
                gScore[neighbor]=tentativeG;
                parent[neighbor]=current;

                int f=tentativeG+manhatanMetric(neighbor, end);
                pq.emplace(f,neighbor);
            }


        }
    }



    return {};


}