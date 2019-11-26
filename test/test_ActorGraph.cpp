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

TEST(ActorGraphTests, MEDIUM_TEST) {
    ActorGraph graph;
    // Assert loading file works
    ASSERT_EQ(graph.loadFromFile("../data/imdb_middle_sample.tsv", false), true);
}

TEST(ActorGraphTests, INVALID_FILE_TEST) {
    ActorGraph graph;
    // Assert loading invalid file returns false
    ASSERT_EQ(graph.loadFromFile("invalid.tsv", false), false);
}