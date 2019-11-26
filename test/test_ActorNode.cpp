#include <iostream>
#include <string>

#include <gtest/gtest.h>
#include "ActorNode.hpp"
#include "MovieEdge.hpp"

using namespace std;
using namespace testing;

// Simple, quick test for ActorNode
TEST(ActorNodeTests, SIMPLE_TEST) {
    ActorNode tom("Tom Johnson");
    MovieEdge w("The Wonderland", 2015, 4);
    MovieEdge n("Nevereverland", 2014, 5);

    tom.addMovie(&w);
    tom.addMovie(&n);

    unordered_set<MovieEdge*> movies;
    movies.insert(&w);
    movies.insert(&n);

    // Assert correct movies stored in movies
    ASSERT_EQ(movies, tom.movies);
}

TEST(ActorNodeTests, SIMPLE_NAME_TEST) {
    ActorNode tom("Tom Johnson");
    // Assert name is correct
    ASSERT_EQ("Tom Johnson", tom.name);
}