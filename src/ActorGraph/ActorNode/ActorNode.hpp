/*
 * ActorNode.hpp
 * Author: Aimee T Shao
 * Date:   11/24/2019
 *
 * ActorNode header file. ActorNode will store the actor's name and the movies
 * the actor has worked in before.
 */
#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP

class MovieEdge;

#include <string>
#include <unordered_set>

using namespace std;

/**
 * ActorNode class that represents a vertex/actor. It stores the actor's name
 * and the movies the actor has worked in before.
 */
class ActorNode {
  protected:
    string name;
    unordered_set<MovieEdge*> movies;

  public:
    /**
     * Explicit Constuctor of the Actor Node.
     * @param actorName Actor's name
     */
    ActorNode(string actorName) : name(actorName), movies(0) {}

    /**
     * Adds a movie into the movies vector to indicate a relationship between
     * this actor and the movie.
     * @param movie Pointer to MovieEdge to add to movies vector
     */
    void addMovie(MovieEdge* movie);

    /**
     * Method to output the name of the actor.
     * @return name of actor
     */
    string getName();

    /**
     * Testing method to check movies vector.
     * @return vector of movies the actor is in
     */
    unordered_set<MovieEdge*> getMovies();
};

#endif  // ACTORNODE_HPP
