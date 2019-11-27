#include <fstream>
#include <iostream>
#include <string>

#include <gtest/gtest.h>
#include "ActorGraph.hpp"
#include "ActorNode.hpp"
#include "MovieEdge.hpp"

using namespace std;
using namespace testing;

TEST(ActorGraphTests, SIMPLE_TEST) {
    ActorGraph graph;
    // Assert loading file works
    ASSERT_EQ(graph.loadFromFile("../data/imdb_small_sample.tsv", true), true);
}

TEST(ActorGraphTests, INVALID_FILE_TEST) {
    ActorGraph graph;
    // Assert loading invalid file returns false
    ASSERT_EQ(graph.loadFromFile("invalid.tsv", false), false);
}

TEST(ActorGraphTests, PATHFIND_TEST) {
    ActorGraph graph;
    graph.loadFromFile("../data/imdb_small_sample.tsv", false);
    const char* pairsFileName = "../data/test_small_pairs.tsv";
    // Assert path finding works
    ASSERT_EQ(graph.pathFind(pairsFileName, cout), true);
}

TEST(ActorGraphTests, LINKPREDICT_TEST) {
    ActorGraph graph;
    graph.loadFromFile("../data/imdb_small_sample.tsv", false);
    const char* actorsFileName = "../data/test_actors.tsv";
    // Assert linkpredictor works
    ASSERT_EQ(graph.linkPredict(actorsFileName, cout, cout), true);
}
