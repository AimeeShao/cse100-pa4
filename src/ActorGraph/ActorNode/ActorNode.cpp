/*
 * ActorNode.cpp
 * Author: Aimee T Shao
 * Date:   11/24/2019
 *
 * ActorNode that serves as a vertex in ActorGraph. ActorNode will store the
 * actor's name and the movies the actor has worked in before.
 */

#include "ActorNode.hpp"

using namespace std;

/**
 * Adds a movie into the movies vector to indicate a relationship between
 * this actor and the movie.
 * @param movie Pointer to MovieEdge to add to movies vector
 */
void ActorNode::addMovie(MovieEdge* movie) { movies.insert(movie); }