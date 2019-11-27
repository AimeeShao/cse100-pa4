/*
 * linkpredictor.cpp
 * Author: Aimee T Shao
 * Date:   11/24/2019
 *
 * Main executable file to find top 4 future interactions and top 4 new
 * collaborations for a given actor. Top interactions means the highest number
 * of paths from the given actor to the current actor and any ties will be
 * sorted alphabetically.
 */
#include <fstream>
#include <iostream>
#include <string>
#include "ActorGraph.hpp"

// output lines
#define READING "Reading "
#define DOTS "..."
#define DONE "done"

// output file lines
#define HEADER "Actor1,Actor2,Actor3,Actor4"

#define NUM_ARGS 5
#define INFILE_IDX 1
#define ACTORSFILE_IDX 2
#define COLLABFILE_IDX 3
#define NONCOLLABFILE_IDX 4

/**
 * Builds graph based on infile and predicts 4 top links for collaborated and
 * non collaborated groups for each actor in the actorFile.
 * @param inFileName Input file name
 * @param actorsFileName File identifying actors to find top interactions for
 * @param collabFileName File to output collaborated group of interactions
 * @param noncollabFileName File to output non collaborated group
 * @return 0 if succesful, Error if not.
 */
int linkpredict(const char* inFileName, const char* actorsFileName,
                const char* collabFileName, const char* noncollabFileName) {
    // read and create graph
    ActorGraph graph;
    cout << READING << inFileName << DOTS << endl;
    graph.loadFromFile(inFileName, false);
    cout << DONE << endl;

    // set up output file
    ofstream collabOut(collabFileName);
    ofstream noncollabOut(noncollabFileName);
    collabOut << HEADER << endl;
    noncollabOut << HEADER << endl;

    graph.linkPredict(actorsFileName, collabOut, noncollabOut);
    collabOut.close();
    noncollabOut.close();

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

    // path find
    linkpredict(argv[INFILE_IDX], argv[ACTORSFILE_IDX], argv[COLLABFILE_IDX],
                argv[NONCOLLABFILE_IDX]);

    return 0;
}