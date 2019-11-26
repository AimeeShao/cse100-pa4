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
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define CUR_YEAR 2019
using namespace std;

/**
 * Constructor of the Actor graph
 */
ActorGraph::ActorGraph(void) : numEdges(0), actors(0), movies(0) {}

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
