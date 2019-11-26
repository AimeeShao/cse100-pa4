/*
 * ActorGraph.cpp
 * Author: Aimee T Shao
 * Date:   11/24/2019
 *
 * This file is meant to exist as a container for starter code that you can use
 * to read the input file format defined in imdb_2019.tsv. Feel free to modify
 * any/all aspects as you wish.
 */

#include "ActorGraph.hpp"
#include <limits.h>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#define CUR_YEAR 2019
#define DOUBLE 2

// string literals for outputting
#define OPEN_P "("
#define CLOSE_P ")"
#define OPEN_S "["
#define CLOSE_S "]"
#define TO_MOVIE "--"
#define TO_ACTOR "-->"

using namespace std;

/**
 * Constructor of the Actor graph
 */
ActorGraph::ActorGraph(void) : numEdges(0), actors(0), movies(0) {}

/**
 * Deconstructor of the Actor graph. Deletes all the ActorNodes and MovieEdges
 */
ActorGraph::~ActorGraph() {
    for (pair<string, ActorNode*> actor : actors) {
        delete (actor.second);
    }
    for (pair<string, MovieEdge*> movie : movies) {
        delete (movie.second);
    }
}

/** You can modify this method definition as you wish
 *
 * Load the graph from a tab-delimited file of actor->movie relationships.
 *
 * in_filename - input filename
 * use_weighted_edges - if true, compute edge weights as 1 + (2019 -
 * movie_year), otherwise all edge weights will be 1
 *
 * return true if file was loaded sucessfully, false otherwise
 */
bool ActorGraph::loadFromFile(const char* in_filename,
                              bool use_weighted_edges) {
    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;

    // keep reading lines until the end of file is reached
    while (infile) {
        string s;

        // get the next line
        if (!getline(infile, s)) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss(s);
        vector<string> record;

        while (ss) {
            string str;

            // get the next string before hitting a tab character and put it in
            // 'str'
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }

        string actor(record[0]);
        string movie_title(record[1]);
        int year = stoi(record[2]);

        // Create pointers to hold the actor and movie
        ActorNode* actorNode = nullptr;
        MovieEdge* movieEdge = nullptr;

        // Check if actor already exists. If not, create new actor
        if (actors.find(actor) == actors.end()) {
            actorNode = new ActorNode(actor);
            actors[actor] = actorNode;
        } else {  // If exist, use pointer to actor
            actorNode = actors[actor];
        }

        string movieName = movie_title + to_string(year);
        // Check if movie exists already. If not, create new movie
        if (movies.find(movieName) == movies.end()) {
            // consider weighed or unweighed edges
            if (use_weighted_edges) {
                movieEdge =
                    new MovieEdge(movie_title, year, 1 + (CUR_YEAR - year));
            } else {
                movieEdge = new MovieEdge(movie_title, year, 1);
            }
            movies[movieName] = movieEdge;
        } else {  // If exist, use pointer to movie
            movieEdge = movies[movieName];
        }

        // add relationships
        actorNode->addMovie(movieEdge);
        movieEdge->addActor(actorNode);
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();
    return true;
}

/**
 * Read pairs file and output the expected output to the output file.
 * @param pairs_filename Pairs filename
 * @param out ofstream of output file to output to
 * @return true if path find was sucessful, false otherwise
 */

bool ActorGraph::pathFind(const char* pairs_filename, ostream& out) {
    // Initialize the file stream
    ifstream pairsfile(pairs_filename);

    bool have_header = false;

    // keep reading lines until the end of file is reached
    while (pairsfile) {
        string s;

        // get the next line
        if (!getline(pairsfile, s)) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss(s);
        vector<string> record;

        while (ss) {
            string str;

            // get the next string before hitting a tab character and put it in
            // 'str'
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        if (record.size() != DOUBLE) {
            // we should have exactly 2 columns
            continue;
        }

        string actorStart(record[0]);
        string actorEnd(record[1]);

        // check if these two actors exist. If not, then just empty line
        if (actors.find(actorStart) == actors.end() ||
            actors.find(actorEnd) == actors.end()) {
            out << endl;
            continue;
        }

        // Path finding
        // set initial values for actors
        for (pair<string, ActorNode*> actor : actors) {
            actor.second->dist = INT_MAX;
            actor.second->prev = pair<ActorNode*, MovieEdge*>(nullptr, nullptr);
        }

        // BFS Approach to path finding
        queue<ActorNode*> toExplore;
        ActorNode* start = actors[actorStart];
        start->dist = 0;
        toExplore.push(start);

        while (!toExplore.empty()) {  // loop until all are visited
            ActorNode* next = toExplore.front();
            toExplore.pop();

            if (next == actors[actorEnd]) {  // found end actor so stop looking
                break;
            }

            for (MovieEdge* movie : next->movies) {       // loop movies
                for (ActorNode* actor : movie->actors) {  // loop neighbors
                    if (actor->dist == INT_MAX) {         // if not visited yet
                        actor->dist = next->dist + 1;
                        actor->prev = pair<ActorNode*, MovieEdge*>(next, movie);
                        toExplore.push(actor);
                    }
                }
            }
        }

        // traverse backwards from actorEnd to actorStart
        vector<string> traversal;
        traversal.push_back(actors[actorEnd]->name);
        pair<ActorNode*, MovieEdge*> pair = actors[actorEnd]->prev;

        // loop until we hit actorStart
        while (pair.first != nullptr && pair.second != nullptr) {
            traversal.push_back(pair.second->getName());
            traversal.push_back(pair.first->name);
            pair = pair.first->prev;
        }

        // traverse backwards in traversal and print out expected output
        for (int i = traversal.size() - 1; i >= 0; i--) {
            if (i % DOUBLE == 0) {  // actors
                out << OPEN_P << traversal[i] << CLOSE_P;
                if (i != 0) {  // not last actor
                    out << TO_MOVIE;
                }
            } else {  // movie
                out << OPEN_S << traversal[i] << CLOSE_S << TO_ACTOR;
            }
        }

        out << endl;
    }
    return true;
}
