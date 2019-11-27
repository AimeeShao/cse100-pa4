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

    /**
     * Predicts 4 top links for collaborated and non collaborated groups for
     * each actor in the actorFile.
     * @param actorsFileName File identifying actors to find top interactions
     * for
     * @param collabOut ostream to output collaborated group of interactions
     * @param noncollabOut ostream to output non collaborated group links
     * @return true if link predict find was sucessful, false otherwise
     */
    bool linkPredict(const char* actorsFileName, ostream& collabOut,
                     ostream& noncollabOut);
};

/* Comparator for linkpredictor. In priority queue, first compare counts, higher
 * count has more priority. If tie, compare string, lower ascii has more
 * priority.
 */
struct LinkPredComp {
    /* The comparator or compare method for linkpredictor. First compare counts,
     * higher count has more priority. If tie, compare string, lower ascii has
     * more priority.
     * @param lhs first pair to compare containing count and actor name
     * @param rhs second pair to cmopare containing count and actor name
     * @return True if lhs has lower priority than rhs
     *         False if lhs has higher priority than rhs.
     */
    bool operator()(pair<int, string>& lhs, pair<int, string>& rhs) const {
        // compare count
        if (lhs.first < rhs.first) {  // rhs has higher priority
            return true;
        } else if (lhs.first > rhs.first) {  // lhs has higher priority
            return false;
        } else {  // counts are same, so compare ascii values
            if (lhs.second > rhs.second) {  // lhs ascii high, so lower priority
                return true;
            } else {  // lhs has higher priority, rhs has lower priority
                return false;
            }
        }
    }
};

#endif  // ACTORGRAPH_HPP
