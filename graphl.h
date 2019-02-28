/** ------------------------- graphl.h ---------------------------------
    Chaconne Tatum-Diehl 502A
    2/14/2019
    2/18/2019
    --------------------------------------------------------------------
    Purpose - Header file for the GraphL class, which implements an
    unweighted digraph using an adjacency list
    --------------------------------------------------------------------
    GraphL uses an array of GraphNode structs to store the graph data.
    Each GraphNode contains the head of list of EdgeNodes which store
    information about which other nodes in the graph that GraphNode is
    connected to

    A depth-first traversal is implemented using recursion
    -------------------------------------------------------------------- */

#ifndef GRAPHL_H
#define GRAPHL_H

#include "graphm.h"
#include "nodedata.h"

using namespace std;

class GraphL
{
private:
    struct EdgeNode;      // forward reference for the compiler
    struct GraphNode
    {    // structs used for simplicity, use classes if desired
        EdgeNode* edgeHead = nullptr; // head of the list of edges
        NodeData* data = nullptr;     // data information about each node
        bool visited = false;
    };

    struct EdgeNode
    {
        int adjGraphNode;  // subscript of the adjacent graph node
        EdgeNode* nextEdge = nullptr;
    };

    GraphNode nodes[MAXNODES];
    int size;

public:
/* --------------------- Default Constructor ---------------------------
   Description: initializes size to 0
   --------------------------------------------------------------------- */
    GraphL();
/* -------------------------- Destructor -------------------------------
   Description: releases memory dynamically allocated for EdgeNodes and
   NodeDatas
   --------------------------------------------------------------------- */
    ~GraphL();


/* -------------------------- buildGraph() -----------------------------
   Description: builds the graph given a text file containing the graph
   data
   Does no input validation, relies on properly formatted input
   --------------------------------------------------------------------- */
    void buildGraph(ifstream& infile);

/* ------------------------ displayGraph() -----------------------------
   Description: prints the graph, showing the name of each node and each
   of its connections with other nodes
   --------------------------------------------------------------------- */
    void displayGraph();

/* ----------------------- depthFirstSearch() --------------------------
   Description: contrary to the name, this is a depth-first traversal
   rather than a search
   Displays the order of the graph when traversed depth-first starting
   from the first node
   --------------------------------------------------------------------- */
    void depthFirstSearch();

/* ----------------------- depthFirstHelper() --------------------------
   Description: recursive helper function for depthFirstSearch()
   --------------------------------------------------------------------- */
    void depthFirstHelper(int currNode);
};

#endif // GRAPHL_H
