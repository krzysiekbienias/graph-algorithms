#include <gtest/gtest.h>
#include "graph.hpp"
#include "mst/prim.hpp"


TEST(PrimAlgo,BaseCase) {
  std::vector<std::vector<std::vector<int>>>in ={
    {
      {1, 3},
      {2, 5}
    },
    {
          {0, 3},
          {2, 10},
          {3, 12},
    },
    {
          {0, 5},
          {1, 10},
    },
    {
          {1, 12}
    }
  };
    std::vector<std::vector<std::vector<int>>> actual=primsAlgorithm(in);
    std::vector<std::vector<std::vector<int>>> expected={
        {{1,3},{2,5}},
        {{0,3},{3,12}},
        {{0,5}},
        {{1,12}}};
    EXPECT_EQ(actual,expected);
}


TEST(PrimAlgo,BiggerGraph) {
    std::vector<std::vector<std::vector<int>>>in ={
        
      {
        {1, 3},
        {2, 5}
      },
    {
      {0, 3},
      {2, 12},
      {3, 20},
      {4, 3}
    },
    {
      {0, 5},
      {1, 12},
      {3, 14},
      {6, 10}
    },
    {
      {1, 20},
      {2, 14},
      {4, 2}
    },
    {
      {1, 3},
      {3, 2},
      {5, 11}
    },
    {
      {4, 11},
      {6, 2}
    },
    {
      {2, 10},
      {5, 2},
      {7, 100}
    },
    {
      {6, 100}
    }
  
    };
    std::vector<std::vector<std::vector<int>>> actual=primsAlgorithm(in);
    std::vector<std::vector<std::vector<int>>> expected={

    };
    EXPECT_EQ(actual,expected);
}
