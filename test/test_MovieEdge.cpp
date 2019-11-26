#include <iostream>
#include <string>

#include <gtest/gtest.h>
#include "ActorNode.hpp"
#include "MovieEdge.hpp"

using namespace std;
using namespace testing;

// Simple, quick test for MovieEdge
TEST(MovieEdgeTests, SIMPLE_TEST) {
    MovieEdge oz("Wizard of Oz", 2000, 1);
    ActorNode tom("Tom Johnson");
    ActorNode alice("Alice Wonderland");

    oz.addActor(&tom);
    oz.addActor(&alice);

    unordered_set<ActorNode*> actors;
    actors.insert(&tom);
    actors.insert(&alice);

    // Assert correct actors stored in movies
    ASSERT_EQ(actors, oz.getActors());
}

TEST(MovieEdgeTests, SIMPLE_NAME_TEST) {
    MovieEdge oz("Wizard of Oz", 2018, 1);
    // Assert name is correct
    ASSERT_EQ("Wizard of Oz#@2018", oz.getName());
}

TEST(MovieEdgeTests, EQUALITY_TEST) {
    MovieEdge oz1("Wizard of Oz", 2009, 1);
    MovieEdge oz2("Wizard of Oz", 2004, 1);

    // Assert inequality
    ASSERT_EQ(oz1 == oz2, false);

    // Assert equality
    MovieEdge check("Wizard of Oz", 2009, 1);
    ASSERT_EQ(oz1 == check, true);
}