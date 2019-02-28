/** ------------------------- graphm.cpp -------------------------------
    Chaconne Tatum-Diehl 502A
    2/14/2019
    2/18/2019
    --------------------------------------------------------------------
    Purpose - Implementation file for the GraphM class, which implements
    a weighted digraph using an adjacency matrix.
    --------------------------------------------------------------------
    GraphM uses a 2D array to represent connections between graph nodes
    and an array of NodeData to store the data contained in the graph's
    nodes.

    An array of TableType helper structures is used to implement
    Dijkstra's algorithm

    No memory is dynamically allocated

    Uses stringstreams to easily convert between characters and integers
    when displaying graph contents
    -------------------------------------------------------------------- */

#include <climits>
#include <cmath>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

#include "graphm.h"

using namespace std;

/* --------------------- Default Constructor ---------------------------
   Description: zeros the size, TableType array, and cost array. Cost
   array is "zeroed" by setting all values to -1, which is used as a
   flag to indicate no connection
   --------------------------------------------------------------------- */
GraphM::GraphM() : size(0)
{
    //zero TableType array
    zeroT();

    //zero cost array
    for(int i = 0; i < MAXNODES; i++)
    {
        for(int j = 0; j < MAXNODES; j++)
        {
            C[i][j] = -1;
        }
    }
}


/* ---------------------------- zeroT() --------------------------------
   Description: sets values in TableType array to defaults
   --------------------------------------------------------------------- */
void GraphM::zeroT()
{
    for(int i = 0; i < MAXNODES; i++)
    {
        for(int j = 0; j < MAXNODES; j++)
        {
            T[i][j].visited = false;
            //INT_MAX used to represent infinity
            T[i][j].dist = INT_MAX;
            //no 0 node exists, so 0 is used here as a flag to indicate
            //no previous pathway
            T[i][j].path = 0;
        }
    }
}


/* -------------------------- buildGraph() -----------------------------
   Description: builds the graph given a text file containing the graph
   data
   Does no input validation, relies on properly formatted input
   --------------------------------------------------------------------- */
void GraphM::buildGraph(ifstream& infile)
{
    infile >> size;
    //discards newline
    infile.get();

    //inserts a NodeData with the read in node name into the graph
    for(int i = 1; i <= size; i++)
    {
        string temp;
        getline(infile, temp);
        NodeData n(temp);
        data[i] = n;
    }

    int node1, node2, weight;
    //stop if we reach end of file or read in a zero
    while(infile >> node1 >> node2 >> weight)
    {
        if(node1 == 0)
        {
            break;
        }
        insertEdge(node1, node2, weight);
    }
}


/* -------------------------- insertEdge() -----------------------------
   Description: inserts an edge into the cost array of the graph
   --------------------------------------------------------------------- */
void GraphM::insertEdge(int node1, int node2, int weight)
{
    C[node1][node2] = weight;
}


/* -------------------------- removeEdge() -----------------------------
   Description: removes an edge into the cost array of the graph
   -1 is used to indicate no connection
   --------------------------------------------------------------------- */
void GraphM::removeEdge(int node1, int node2, int weight)
{
    C[node1][node2] = -1;
}


/* ---------------------- findShortestPath() ---------------------------
   Description: Uses Dijkstra's algorithm to find the shortest path from
   each node in the graph to each other node
   --------------------------------------------------------------------- */
void GraphM::findShortestPath()
{
    for (int source = 1; source <= size; source++)
    {
        //distance between a node and itself is always 0
        T[source][source].dist = 0;
        int currNode;
        for(int i = 1; i <= size; i++)
        {
            //find next node to visit
            int shortest = INT_MAX;
            for(int j = 1; j <= size; j++)
            {
                if(!T[source][j].visited && T[source][j].dist < shortest)
                {
                    currNode = j;
                    shortest = T[source][j].dist;
                }
            }

            //visit new node
            T[source][currNode].visited = true;

            for(int k = 1; k <= size; k++)
            {
                //if a path to another unvisited node exists
                if(C[currNode][k] != -1 && !T[source][k].visited)
                {
                    //if that path is shorter than the current shortest
                    //path between the source and the new unvisited node
                    if(T[source][k].dist >
                       T[source][currNode].dist + C[currNode][k])
                    {
                        //update the TableType array with the new distance
                        //and path data
                        T[source][k].dist = T[source][currNode].dist
                                            + C[currNode][k];
                        T[source][k].path = currNode;
                    }
                }
            }
        }
    }

}


/* ------------------------ displayAll() -------------------------------
   Description: prints the graph, showing shortest paths between nodes
   (if they exist) and the weight of the path
   --------------------------------------------------------------------- */
void GraphM::displayAll()
{
    cout << left << setw(26) << "Description" << setw(11) << "From node"
         << setw(9) << "To node" << setw(12) << "Dijkstra's"
         << setw(9) << "Path" << endl;

    //displays the path from each node to each other node
    for(int i = 1; i <= size; i++)
    {
        cout << setw(26) << data[i] << endl;
        for(int j = 1; j <= size; j++)
        {
            //does not display the path from a node to itself
            if(i != j)
            {
                cout << setw(26) << "";
                displayLine(i, j);
            }
        }
    }
    cout << endl;
}


/* --------------------------- display() -------------------------------
   Description: displays a the path and distance between two nodes, then
   displays the names of the nodes traversed
   --------------------------------------------------------------------- */
void GraphM::display(int from, int to)
{
    string pathstr = displayLine(from, to);
    stringstream ss(pathstr);

    //displays names of traversed nodes using the string containing the
    //path returned from displayLine()
    int i;
    while(ss >> i)
    {
        cout << data[i] << endl << endl;
    }
    cout << endl;
}


/* ------------------------ displayLine() ------------------------------
   Description: helper function for display() and displayAll() functions
   Prints a single line displaying the distance of the shortest path
   from one node to another and the nodes traversed on that path
   Returns the string indicating the path
   --------------------------------------------------------------------- */
string GraphM::displayLine(int from, int to)
{
    stringstream ss;
    string pathstr = "";
    string temp = "";

    cout << setw(11) << from << setw(9) << to << setw(12);

    //if no path exists don't print distance or path
    if(T[from][to].dist == INT_MAX)
    {
        cout << "---";
    }
    else
    {
        cout << T[from][to].dist;
        int c = to;

        //traverse backwards through the path, using a stringstream to
        //store the entire path as we go
        while(c != 0)
        {
            ss << c << " ";
            c = T[from][c].path;
        }

        //reverse the backwards path to print in correct order
        while(ss >> temp)
        {
            pathstr = temp + " " + pathstr;
        }
        cout << setw(9) << pathstr;
    }
    cout << endl;
    return pathstr;
}
