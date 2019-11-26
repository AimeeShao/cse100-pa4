/*
 * MovieEdge.cpp
 * Author: Aimee T Shao
 * Date:   11/24/2019
 *
 * MovieEdge serves as an edge in the ActorGraph that
 * contains the movie's name and actors who played in the movie.
 */

#include "MovieEdge.hpp"

#define SPACING "#@"

using namespace std;

/**
 * Adds an actor into the actors vector to indicate a relationship between
 * the actor and this movie.
 * @param actor Pointer to ActorNode to add an actor to actors vector
 */
void MovieEdge::addActor(ActorNode* actor) { actors.insert(actor); }

/**
 * Override equality operator. If name and year are the same, then they are
 * equal. Otherwise they are not.
 * @param movie movie to compare with this movie
 * @return True if equal (name and year). Otherwise, false.
 */
bool MovieEdge::operator==(const MovieEdge& movie) {
    // equal if name and year are the same
    return (name == movie.name && year == movie.year);
}

/**
 * Method to output information about the movie.
 * @return string with name and year of movie.
 */
string MovieEdge::getName() { return name + SPACING + to_string(year); }

/**
 * Testing method to check actors vector.
 * @return unordered set of actors who have played in the movie.
 */
unordered_set<ActorNode*> MovieEdge::getActors() { return actors; }