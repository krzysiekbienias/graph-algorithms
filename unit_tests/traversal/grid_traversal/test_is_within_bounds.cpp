#include "gtest/gtest.h"
#include "traversal/grid_traversal/is_within_bounds.hpp"


TEST(IsWithinBoundsIntMatrix, ReturnsFalseForEmptyMatrix) {
    std::vector<std::vector<int>> matrix;

    EXPECT_FALSE(isWithinBounds(0, 0, matrix));
    EXPECT_FALSE(isWithinBounds(-1, 0, matrix));
    EXPECT_FALSE(isWithinBounds(0, -1, matrix));
}

TEST(IsWithinBoundsIntMatrix, ReturnsTrueForTopLeftCell) {
    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6}
    };

    EXPECT_TRUE(isWithinBounds(0, 0, matrix));
}

TEST(IsWithinBoundsIntMatrix, ReturnsTrueForBottomRightCell) {
    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6}
    };

    EXPECT_TRUE(isWithinBounds(1, 2, matrix));
}

TEST(IsWithinBoundsIntMatrix, ReturnsTrueForMiddleCell) {
    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    EXPECT_TRUE(isWithinBounds(1, 1, matrix));
}

TEST(IsWithinBoundsIntMatrix, ReturnsFalseForNegativeRow) {
    std::vector<std::vector<int>> matrix = {
        {1, 2},
        {3, 4}
    };

    EXPECT_FALSE(isWithinBounds(-1, 0, matrix));
}

TEST(IsWithinBoundsIntMatrix, ReturnsFalseForNegativeColumn) {
    std::vector<std::vector<int>> matrix = {
        {1, 2},
        {3, 4}
    };

    EXPECT_FALSE(isWithinBounds(0, -1, matrix));
}

TEST(IsWithinBoundsIntMatrix, ReturnsFalseForRowEqualToRowCount) {
    std::vector<std::vector<int>> matrix = {
        {1, 2},
        {3, 4}
    };

    EXPECT_FALSE(isWithinBounds(2, 0, matrix));
}

TEST(IsWithinBoundsIntMatrix, ReturnsFalseForColumnEqualToColumnCount) {
    std::vector<std::vector<int>> matrix = {
        {1, 2},
        {3, 4}
    };

    EXPECT_FALSE(isWithinBounds(0, 2, matrix));
}

TEST(IsWithinBoundsCharMatrix, ReturnsFalseForEmptyMatrix) {
    std::vector<std::vector<char>> matrix;

    EXPECT_FALSE(isWithinBounds(0, 0, matrix));
    EXPECT_FALSE(isWithinBounds(-1, 0, matrix));
    EXPECT_FALSE(isWithinBounds(0, -1, matrix));
}

TEST(IsWithinBoundsCharMatrix, ReturnsTrueForTopLeftCell) {
    std::vector<std::vector<char>> matrix = {
        {'a', 'b', 'c'},
        {'d', 'e', 'f'}
    };

    EXPECT_TRUE(isWithinBounds(0, 0, matrix));
}

TEST(IsWithinBoundsCharMatrix, ReturnsTrueForBottomRightCell) {
    std::vector<std::vector<char>> matrix = {
        {'a', 'b', 'c'},
        {'d', 'e', 'f'}
    };

    EXPECT_TRUE(isWithinBounds(1, 2, matrix));
}

TEST(IsWithinBoundsCharMatrix, ReturnsFalseForNegativeRow) {
    std::vector<std::vector<char>> matrix = {
        {'a', 'b'},
        {'c', 'd'}
    };

    EXPECT_FALSE(isWithinBounds(-1, 0, matrix));
}

TEST(IsWithinBoundsCharMatrix, ReturnsFalseForNegativeColumn) {
    std::vector<std::vector<char>> matrix = {
        {'a', 'b'},
        {'c', 'd'}
    };

    EXPECT_FALSE(isWithinBounds(0, -1, matrix));
}

TEST(IsWithinBoundsCharMatrix, ReturnsFalseForRowEqualToRowCount) {
    std::vector<std::vector<char>> matrix = {
        {'a', 'b'},
        {'c', 'd'}
    };

    EXPECT_FALSE(isWithinBounds(2, 0, matrix));
}

TEST(IsWithinBoundsCharMatrix, ReturnsFalseForColumnEqualToColumnCount) {
    std::vector<std::vector<char>> matrix = {
        {'a', 'b'},
        {'c', 'd'}
    };

    EXPECT_FALSE(isWithinBounds(0, 2, matrix));
}

TEST(IsWithinBoundsDimensions, ReturnsTrueForTopLeftCell) {
    EXPECT_TRUE(isWithinBounds(0, 0, 2, 3));
}

TEST(IsWithinBoundsDimensions, ReturnsTrueForBottomRightCell) {
    EXPECT_TRUE(isWithinBounds(1, 2, 2, 3));
}

TEST(IsWithinBoundsDimensions, ReturnsTrueForMiddleCell) {
    EXPECT_TRUE(isWithinBounds(1, 1, 3, 3));
}

TEST(IsWithinBoundsDimensions, ReturnsFalseForNegativeRow) {
    EXPECT_FALSE(isWithinBounds(-1, 0, 2, 3));
}

TEST(IsWithinBoundsDimensions, ReturnsFalseForNegativeColumn) {
    EXPECT_FALSE(isWithinBounds(0, -1, 2, 3));
}

TEST(IsWithinBoundsDimensions, ReturnsFalseForRowEqualToRowCount) {
    EXPECT_FALSE(isWithinBounds(2, 0, 2, 3));
}

TEST(IsWithinBoundsDimensions, ReturnsFalseForColumnEqualToColumnCount) {
    EXPECT_FALSE(isWithinBounds(0, 3, 2, 3));
}

TEST(IsWithinBoundsDimensions, ReturnsFalseWhenRowsAndColsAreZero) {
    EXPECT_FALSE(isWithinBounds(0, 0, 0, 0));
}