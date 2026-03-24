#include <vector>



bool isWithinBounds(int r, int c,const std::vector<std::vector<int>>& matrix) {
    int rows=0;
    int cols=0;
    if (!matrix.empty()) {
        rows=(int)matrix.size();
        cols=(int)matrix[0].size();
    }
    if (r>=0 && r<rows && c>=0 && c<cols) {
        return true;
    }
    return false;
}


bool isWithinBounds(int r, int c,const std::vector<std::vector<char>>& matrix) {
    int rows=0;
    int cols=0;
    if (!matrix.empty()) {
        rows=(int)matrix.size();
        cols=(int)matrix[0].size();
    }
    if (r>=0 && r<rows && c>=0 && c<cols) {
        return true;
    }
    return false;
}

//another version without reference to the matrix itself.
bool isWithinBounds(int r, int c, int rows, int cols) {
    return r >= 0 && r < rows && c >= 0 && c < cols;
}