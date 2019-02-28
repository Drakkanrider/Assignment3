/** ------------------------- graphm.h ---------------------------------
    Chaconne Tatum-Diehl 502A
    2/14/2019
    2/18/2019
    --------------------------------------------------------------------
    Purpose - Header file for the GraphM class, which implements a
    weighted digraph using an adjacency matrix.
    --------------------------------------------------------------------
    GraphM uses a 2D array to represent connections between graph nodes
    and an array of NodeData to store the data contained in the graph's
    nodes.

    An array of TableType helper structures is used to implement
    Dijkstra's algorithm
    -------------------------------------------------------------------- */

#ifndef GRAPHM_H
#define GRAPHM_H

#include <iostream>

#include "nodedata.h"

using namespace std;

const int MAXNODES = 256;

class GraphM
{
private:
    struct TableType
    {
        bool visited;          // whether node has been visited
        int dist;              // shortest distance from source known so far
        int path;              // previous node in path of min dist
    };

    NodeData data[MAXNODES];              // data for graph nodes
    int C[MAXNODES][MAXNODES];            // Cost array, the adjacency matrix
    int size;                             // number of nodes in the graph
    TableType T[MAXNODES][MAXNODES];      // stores visited, distance, path

public:
/* --------------------- Default Constructor ---------------------------
   Description: zeros the size, TableType array, and cost array. Cost
   array is "zeroed" by setting all values to -1, which is used as a
   flag to indicate no connection
   --------------------------------------------------------------------- */
    GraphM();


/* ---------------------------- zeroT() --------------------------------
   Description: sets values in TableType array to defaults
   --------------------------------------------------------------------- */
    void zeroT();

/* -------------------------- buildGraph() -----------------------------
   Description: builds the graph given a text file containing the graph
   data
   Does no input validation, relies on properly formatted input
   --------------------------------------------------------------------- */
    void buildGraph(ifstream& infile);

/* -------------------------- insertEdge() -----------------------------
   Description: inserts an edge into the cost array of the graph
   --------------------------------------------------------------------- */
    void insertEdge(int node1, int node2, int weight);

/* -------------------------- removeEdge() -----------------------------
   Description: removes an edge into the cost array of the graph
   -1 is used to indicate no connection
   --------------------------------------------------------------------- */
    void removeEdge(int node1, int node2, int weight);

/* ---------------------- findShortestPath() ---------------------------
   Description: Uses Dijkstra's algorithm to find the shortest path from
   each node in the graph to each other node
   --------------------------------------------------------------------- */
    void findShortestPath();

/* ------------------------ displayAll() -------------------------------
   Description: prints the graph, showing shortest paths between nodes
   (if they exist) and the weight of the path
   --------------------------------------------------------------------- */
    void displayAll();

/* --------------------------- display() -------------------------------
   Description: displays a the path and distance between two nodes, then
   displays the names of the nodes traversed
   --------------------------------------------------------------------- */
    void display(int from, int to);

/* ------------------------ displayLine() ------------------------------
   Description: helper function for display() and displayAll() functions
   Prints a single line displaying the distance of the shortest path
   from one node to another and the nodes traversed on that path
   Returns the string indicating the path
   --------------------------------------------------------------------- */
    string displayLine(int from, int to);
};

#endif // GRAPHM_H
