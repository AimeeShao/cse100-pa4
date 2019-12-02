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
    ASSERT_EQ(graph.loadFromFile("../test/data/imdb_small_sample.tsv", true),
              true);
}

TEST(ActorGraphTests, INVALID_FILE_TEST) {
    ActorGraph graph;
    // Assert loading invalid file returns false
    ASSERT_EQ(graph.loadFromFile("../test/data/invalid.tsv", false), false);
}

TEST(ActorGraphTests, PATHFIND_TEST) {
    ActorGraph graph;
    graph.loadFromFile("../test/data/imdb_small_sample.tsv", false);
    const char* pairsFileName = "../test/data/test_small_pairs.tsv";
    // Assert path finding works
    ASSERT_EQ(graph.pathFind(pairsFileName, cout), true);
}

TEST(ActorGraphTests, LINKPREDICT_TEST) {
    ActorGraph graph;
    graph.loadFromFile("../test/data/imdb_small_sample.tsv", false);
    const char* actorsFileName = "../test/data/test_actors.tsv";
    // Assert linkpredictor works
    ASSERT_EQ(graph.linkPredict(actorsFileName, cout, cout), true);
}

TEST(ActorGraphTests, MOVIETRAVEL_TEST) {
    ActorGraph graph;
    graph.loadFromFile("../test/data/imdb_small_sample.tsv", true);
    // Assert movietravel works
    ASSERT_EQ(graph.movieTravel(cout), true);
}