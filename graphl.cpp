/** ------------------------- graphl.cpp -------------------------------
    Chaconne Tatum-Diehl 502A
    2/14/2019
    2/18/2019
    --------------------------------------------------------------------
    Purpose - Implementation file for the GraphL class, which implements
    an unweighted digraph using an adjacency list
    --------------------------------------------------------------------
    GraphL uses an array of GraphNode structs to store the graph data.
    Each GraphNode contains the head of list of EdgeNodes which store
    information about which other nodes in the graph that GraphNode is
    connected to

    A depth-first traversal is implemented using recursion
    -------------------------------------------------------------------- */

#include <iostream>
#include <iomanip>
#include <sstream>

#include "graphl.h"

using namespace std;

/* --------------------- Default Constructor ---------------------------
   Description: initializes size to 0
   --------------------------------------------------------------------- */
GraphL::GraphL() : size(0){}


/* -------------------------- Destructor -------------------------------
   Description: releases memory dynamically allocated for EdgeNodes and
   NodeDatas
   --------------------------------------------------------------------- */
GraphL::~GraphL()
{
    for(int i = 1; i <= size; i++)
    {
        EdgeNode* pWalk = nodes[i].edgeHead;
        //deletes all EdgeNodes for each node
        while(pWalk)
        {
            EdgeNode* temp = pWalk->nextEdge;
            delete pWalk;
            pWalk = temp;
        }
        //then deletes NodeData
        delete nodes[i].data;
    }
}


/* -------------------------- buildGraph() -----------------------------
   Description: builds the graph given a text file containing the graph
   data
   Does no input validation, relies on properly formatted input
   --------------------------------------------------------------------- */
void GraphL::buildGraph(ifstream& infile)
{
    infile >> size;
    //discards newline
    infile.get();

    //dynamically allocates a new NodeData for each node using the node
    //names from the file
    for(int i = 1; i <= size; i++)
    {
        string temp;
        getline(infile, temp);
        NodeData* n = new NodeData(temp);
        nodes[i].data = n;
    }

    //dynamically allocates a new EdgeNode for each connection in the file
    //and adds it to the adjacency list of the appropriate node
    int from, to;
    while(infile >> from >> to)
    {
        if(from == 0)
        {
            break;
        }
        EdgeNode* e = new EdgeNode;
        e->adjGraphNode = to;
        e->nextEdge = nodes[from].edgeHead;
        nodes[from].edgeHead = e;
    }
}


/* ------------------------ displayGraph() -----------------------------
   Description: prints the graph, showing the name of each node and each
   of its connections with other nodes
   --------------------------------------------------------------------- */
void GraphL::displayGraph()
{
    cout << "Graph:" << endl;
    for(int i = 1; i <= size; i++)
    {
        stringstream ss;
        ss << "Node " << i;
        cout << left << setw(13) << ss.str() << *(nodes[i].data) << endl
             << endl;

        //displays each connection
        EdgeNode* pWalk = nodes[i].edgeHead;
        while(pWalk)
        {
            cout << right << setw(6) << "edge" << " " << i << " "
            << setw(2) << pWalk->adjGraphNode << endl;
            pWalk = pWalk->nextEdge;
        }
    }
    cout << endl;
}


/* ----------------------- depthFirstSearch() --------------------------
   Description: contrary to the name, this is a depth-first traversal
   rather than a search
   Displays the order of the graph when traversed depth-first starting
   from the first node
   --------------------------------------------------------------------- */
void GraphL::depthFirstSearch()
{
    cout << "Depth-first ordering: ";
    if(size > 0)
    {
        depthFirstHelper(1);
    }
    cout << endl;
}


/* ----------------------- depthFirstHelper() --------------------------
   Description: recursive helper function for depthFirstSearch()
   --------------------------------------------------------------------- */
void GraphL::depthFirstHelper(int currNode)
{
    cout << currNode << " ";
    nodes[currNode].visited = true;

    //looks for new unvisited nodes and recurses on each found
    EdgeNode* pWalk = nodes[currNode].edgeHead;
    while(pWalk)
    {
        if(!nodes[pWalk->adjGraphNode].visited)
        {
            depthFirstHelper(pWalk->adjGraphNode);
        }
        pWalk = pWalk->nextEdge;
    }
}

