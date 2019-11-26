#include <fstream>
#include <iostream>
#include <string>

#include <gtest/gtest.h>
#include "ActorGraph.hpp"
#include "ActorNode.hpp"
#include "MovieEdge.hpp"
#include "pathfinder.cpp"

using namespace std;
using namespace testing;

// Simple test for pathfinder
TEST(MovieEdgeTests, SIMPLE_TEST) {
    const char* inFileName = "../data/imdb_small_sample.tsv";
    const char* weight = "u";
    const char* pairsFileName = "../data/test_small_pairs.tsv";
    const char* outFileName = "../data/out_test_small_pairs.tsv";
    ASSERT_EQ(pathfind(inFileName, weight, pairsFileName, outFileName), 0);
}