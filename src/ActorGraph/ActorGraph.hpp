/*
 * ActorGraph.hpp
 * Author: Aimee T Shao
 * Date:   11/24/2019
 *
 * This file is meant to exist as a container for starter code that you can use
 * to read the input file format defined imdb_2019.tsv. Feel free to modify
 * any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP
#include "ActorNode.hpp"
#include "MovieEdge.hpp"

#include <iostream>
#include <unordered_map>

// Maybe include some data structures here

using namespace std;

/**
 * ActorGraph class that builds up the graph containing nodes with actors and
 * edges that contain the movie the two actors both worked in.
 */
class ActorGraph {
  protected:
    int numEdges;
    unordered_map<string, ActorNode*> actors;
    unordered_map<string, MovieEdge*> movies;

  public:
    /**
     * Constuctor of the Actor graph
     */
    ActorGraph(void);

    /* Deconstructor.
     * Deallocates the memory of the ActorNodes and MovieEdges in ActorGraph.
     */
    ~ActorGraph();

    /**
     * Load the graph from a tab-delimited file of actor->movie relationships.
     * @param in_filename input filename
     * @param use_weighted_edges if true, compute edge weights as 1 + (2019 -
     * movie_year), otherwise all edge weights will be 1
     * @return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* in_filename, bool use_weighted_edges);

    /**
     * Read pairs file and output the expected output to the output file.
     * @param pairs_filename Pairs filename
     * @param out ostream of output file to output to
     * @return true if path find was sucessful, false otherwise
     */

    bool pathFind(const char* pairs_filename, ostream& out);
};

#endif  // ACTORGRAPH_HPP
