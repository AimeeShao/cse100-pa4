/*
 * pathfinder.cpp
 * Author: Aimee T Shao
 * Date:   11/24/2019
 *
 * Main executable file to find the shortest path from one actor to another.
 * Processes the inputs as well.
 */
#include <fstream>
#include <iostream>
#include <string>
#include "ActorGraph.hpp"

#define NUM_ARGS 5
#define INFILE_IDX 1
#define WEIGHT_IDX 2
#define PAIRSFILE_IDX 3
#define OUTFILE_IDX 4

#define UNWEIGHTED "u"
#define WEIGHTED "w"

// output lines
#define READING "Reading "
#define DOTS "..."
#define DONE "done"

// output file lines
#define HEADER "(actor)--[movie#@year]-->(actor)--..."

using namespace std;

/**
 * Performs the processing of inputs and filenames for pathfind. Finds the path
 * from one actor to another after building the graph from the input file.
 * @param inFileName Input file name
 * @param weight u if unweighted graph, w if weighted graph
 * @param pairsFileName File identifying pairs to find path in between
 * @param outFileName File to output to
 * @return 0 if succesful, Error if not.
 */
int pathfind(const char* inFileName, const char* weight,
              const char* pairsFileName, const char* outFileName) {
    bool use_weight;
    // format the weighted
    if (weight == (char*)UNWEIGHTED) {
        use_weight = false;
    } else if (weight == (char*)WEIGHTED) {
        use_weight = true;
    }

    // read and create graph
    ActorGraph graph;
    cout << READING << inFileName << DOTS << endl;
    graph.loadFromFile(inFileName, use_weight);
    cout << DONE << endl;

    // set up output file
    ofstream out(outFileName);
    out << HEADER << endl;

    graph.pathFind(pairsFileName, out);
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
    // quit if invalid number of arguments
    if (argc != NUM_ARGS) {
        exit(0);
    }
    const char* inFileName = argv[INFILE_IDX];
    const char* weight = argv[WEIGHT_IDX];
    const char* pairsFileName = argv[PAIRSFILE_IDX];
    const char* outFileName = argv[OUTFILE_IDX];

    // path find
    pathfind(inFileName, weight, pairsFileName, outFileName);

    return 0;
}