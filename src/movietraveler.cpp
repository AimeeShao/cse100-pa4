/*
 * movietraveler.cpp
 * Author: Aimee T Shao
 * Date:   11/29/2019
 *
 * Main executable file to create a minimum spanning tree using the Kruskal's
 * algorithm for a given inputted connected graph.
 */
#include <fstream>
#include <iostream>
#include <string>
#include "ActorGraph.hpp"

#define INFILE_IDX 1
#define OUTFILE_IDX 2

// output lines
#define READING "Reading "
#define DOTS "..."
#define DONE "done"

// output file lines
#define HEADER "(actor)<--[movie#@year]-->(actor)"

using namespace std;

/**
 * Performs the processing of filenames for movie traveler. Finds the minimum
 * spanning tree using Kruskal's algorithm.
 * @param inFileName Input file name
 * @param outFileName File to output to
 * @return 0 if succesful, Error if not.
 */
int movietraveler(const char* inFileName, const char* outFileName) {
    // read and create graph
    ActorGraph graph;
    graph.loadFromFile(inFileName, true);  // weighted graph

    // set up output file
    ofstream out(outFileName);
    out << HEADER << endl;

    graph.movieTravel(out);
    out.close();

    return 0;
}

/* Main program that runs the compress. Checks if input file is invalid or
 * empty.
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @return 0 if successful. Error otherwise.
 */
int main(int argc, char* argv[]) {
    // path find
    movietraveler(argv[INFILE_IDX], argv[OUTFILE_IDX]);

    return 0;
}