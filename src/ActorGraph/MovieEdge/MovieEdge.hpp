/*
 * MovieEdge.hpp
 * Author: Aimee T Shao
 * Date:   11/24/2019
 *
 * MovieEdge header file. MovieEdge serves as an edge in the ActorGraph that
 * contains the movie's name and actors who played in the movie.
 */
#ifndef MOVIEEDGE_HPP
#define MOVIEEDGE_HPP

class ActorNode;

#include <string>
#include <unordered_set>

using namespace std;

/**
 * MovieEdge class that represents an edge/movie. It stores a movie's name
 * and the actors who worked in the movie.
 */
class MovieEdge {
  public:
    string name;
    int year;
    int weight;
    unordered_set<ActorNode*> actors;

    /**
     * Explicit Constuctor of the MovieEdge.
     * @param movieName Name of the movie
     * @param movieYear Year of the movie
     * @param edgeWeight weight of this movie edge
     */
    MovieEdge(string movieName, int movieYear, int edgeWeight)
        : name(movieName), year(movieYear), weight(edgeWeight), actors(0) {}

    /**
     * Adds an actor into the actors vector to indicate a relationship between
     * the actor and this movie.
     * @param actor Pointer to ActorNode to add an actor to actors vector
     */
    void addActor(ActorNode* actor);

    /**
     * Override equality operator. If name and year are the same, then they are
     * equal. Otherwise they are not.
     * @param movie movie to compare with this movie
     * @return True if equal (name and year). Otherwise, false.
     */
    bool operator==(const MovieEdge& movie);

    /**
     * Method to output information about the movie.
     * @return string with name and year of movie.
     */
    string getName();
};

#endif  // MOVIEEDGE_HPP
