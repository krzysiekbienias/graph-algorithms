#include <vector>

struct Position{
    int row;
    int col;

    bool operator ==(const Position & other ) const{
        return row==other.row && col==other.col;
    }
    
};


struct PositionHash {
    size_t operator()(const Position& p) const noexcept {
        return std::hash<int>{}(p.row) ^ (std::hash<int>{}(p.col) << 1);
    }
};

int manhatanMetric(const Position & p1,const Position& p2);


std::vector<std::vector<int>> aStarAlgorithm(int startRow, int startCol, int endRow, int endCol, std::vector<std::vector<int>> graph);

