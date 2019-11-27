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
#define TOP_LINKS 4

// string literals for outputting
#define OPEN_P "("
#define CLOSE_P ")"
#define OPEN_S "["
#define CLOSE_S "]"
#define TO_MOVIE "--"
#define TO_ACTOR "-->"
#define TAB "\t"

using namespace std;

/**
 * Constructor of the Actor graph
 */
ActorGraph::ActorGraph(void) : actors(0), movies(0) {}

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

/**
 * Predicts 4 top links for collaborated and non collaborated groups for each
 * actor in the actorFile.
 * @param actorsFileName File identifying actors to find top interactions for
 * @param collabOut ostream to output collaborated group of interactions
 * @param noncollabOut ostream to output non collaborated group links
 * @return true if link predict find was sucessful, false otherwise
 */
bool ActorGraph::linkPredict(const char* actorsFileName, ostream& collabOut,
                             ostream& noncollabOut) {
    // Initialize the file stream
    ifstream pairsfile(actorsFileName);

    bool have_header = false;

    // keep reading lines until the end of file is reached
    while (pairsfile) {
        string linkActor;

        // get the next line
        if (!getline(pairsfile, linkActor)) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        // check if given actor exist. If not, then just empty line
        if (actors.find(linkActor) == actors.end()) {
            continue;
        }

        // Link Predictor
        // collab group with their links count with linkActor
        unordered_map<ActorNode*, int> collab;
        unordered_map<ActorNode*, int> collabPriority;

        // get collaborated group with their number of edges with linkActor
        for (MovieEdge* movie : actors[linkActor]->movies) {
            for (ActorNode* actor : movie->actors) {
                if (actor->name != linkActor) {  // not the start actor
                    // not linked yet
                    if (collab.find(actor) == collab.end()) {
                        collab[actor] = 1;
                        collabPriority[actor] = 0;  // priorities are 0 for now
                    } else {
                        collab[actor] += 1;
                    }
                }
            }
        }

        // get collab group's priority. Loop collab group as common neighbor
        for (pair<ActorNode*, int> collabLinks : collab) {
            // loop through movies in collab group
            for (MovieEdge* movie : collabLinks.first->movies) {
                // find third node for the triangle
                for (ActorNode* actor : movie->actors) {
                    if (actor != collabLinks.first &&
                        collab.find(actor) != collab.end()) {
                        // add priority by common neighbor's links w/ linkActor
                        collabPriority[actor] += collabLinks.second;
                    }
                }
            }
        }

        // pq of pair<priority, actor name> to find top 4 link
        priority_queue<pair<int, string>, vector<pair<int, string>>,
                       LinkPredComp>
            pq;

        // push all collabPriorities into pq
        for (pair<ActorNode*, int> actor : collabPriority) {
            pq.push(pair<int, string>(actor.second, actor.first->name));
        }

        // output collab group top links
        for (int i = 0; i < TOP_LINKS; i++) {
            if (pq.empty()) {
                break;
            }
            collabOut << pq.top().second;
            pq.pop();
            if (i != TOP_LINKS - 1) {
                collabOut << TAB;
            }
        }

        // noncollab group with their links count with linkActor
        unordered_map<ActorNode*, int> noncollabPriority;

        // Get noncollab group & priorities. Use collab group as common neighbor
        for (pair<ActorNode*, int> collabLinks : collab) {
            // loop through movies in collab group
            for (MovieEdge* movie : collabLinks.first->movies) {
                // find second connections
                for (ActorNode* actor : movie->actors) {
                    // not linkActor and not in collab group
                    if (actor->name != linkActor &&
                        collab.find(actor) == collab.end()) {
                        // initialize priority to 0
                        if (noncollabPriority.find(actor) ==
                            noncollabPriority.end()) {
                            noncollabPriority[actor] = 0;
                        }
                        // add priority by common neighbor's links w/ linkActor
                        noncollabPriority[actor] += collabLinks.second;
                    }
                }
            }
        }

        // clear pq
        pq = priority_queue<pair<int, string>, vector<pair<int, string>>,
                            LinkPredComp>();

        // push all noncollabPriorities into pq
        for (pair<ActorNode*, int> actor : noncollabPriority) {
            pq.push(pair<int, string>(actor.second, actor.first->name));
        }

        // output noncollab group top links
        for (int i = 0; i < TOP_LINKS; i++) {
            if (pq.empty()) {
                break;
            }
            noncollabOut << pq.top().second;
            pq.pop();
            if (i != TOP_LINKS - 1) {
                noncollabOut << TAB;
            }
        }

        // Add new lines to both files
        collabOut << endl;
        noncollabOut << endl;
    }
    return true;
}