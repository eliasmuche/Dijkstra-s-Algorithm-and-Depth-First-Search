//Elias Muche
//5-6-16
//Program 3 Part 2: DFS

#pragma once
#include "nodedata.h"
#include <iostream>
#include <sstream>
#include "limits.h"
#include <cstring>
#include <algorithm>
#include<stack>
using namespace std;
const int MAX=100;
class GraphL {                           

    public:
		//--------- Default Constructor ------------
		//Initializes size
		//Pre-conditions: none 
		//Post-conditions: size will be 0
		GraphL();
		
		//-------- Destructor ---------
		//De-allocates all pointers (nodedatas and edgenodes)
		//Pre-conditions: none
		//Post-conditions: there will be no memory leaks(all dynamically allocated objects will be de-allocated)
		~GraphL();
		//---------- BuildGraph -------------
		//Takes in a text file and builds a graph based on the text 
		//Pre-conditions: the file must be formatting exactly as shown on canvas 
		//Post-conditions: a graph will be built assuming the pre-conditions were met
    	void buildGraph(istream &in);

		//-------- DisplayGraph ---------
		//Displays the adjacency list as a representation of the graph
		//Pre-conditions: there must be a constructed graph
		//Post-conditions: the list will be displayed
		void displayGraph();

		//---------- DepthFirstSearch ----------
		//Does a depth first search
		//Pre-conditions: there must be a graph to search 
		//Post-conditions: the DFS order will be displayed
		void depthFirstSearch(); 
		
				

    private:
		struct EdgeNode {
	
      		int adjGraphNode;  // subscript of the adjacent graph node

      		EdgeNode* nextEdge=NULL;

  		 };

        struct GraphNode {    // structs used for simplicity, use classes if desired

            EdgeNode* edgeHead=NULL; // head of the list of edges
 
            NodeData *data=NULL;     // data information about each node

            bool visited;               

        };      
		void addAdjNode(EdgeNode *&head,int adjacent);

		//--------- ClearList -----------
		//Takes in an Edge(head of the list) the entire list 
		//Pre-conditions: there must be a constructed graph
		//Post-conditions: the list will be deleted
		void clearList(EdgeNode *&edgeNode);

		//----------- DisplayList --------------
		//Displays the adjacent nodes of a given graph node
		//Pre-conditions: there must be a constructed graph 
		//Post-condtions: all of the adjacent nodes of the graph node will be displayed 
		void displayList(int source, EdgeNode *edgeNode);

		//--------- AllVisited ----------
		//Checks if every graphnode has been visited
		//Pre-conditions: there must be a constructed graph
		//Post-conditions: true or false will be returned
		bool allVisited();

		//---------- NextAdjNode -----------
		//Takes an int(represents a graphnode) and checks to see if a specific graphnode has any more adjacent nodes to visit
		//Also takes another int (represents an adjacent node) that is passed by reference. It will store the next adj node if there's one
		//Pre-conditions: there must be a constructed graph
		//Post-conditions: returns true if there's another unvisited graph node, false if they have all been visited
		bool nextAdjNode(int graphnode, int &adjacent);

		//----------- FindNextGraphNode -------------
		//Finds the next unvisited graphnode
		//Will only be called if we can't dfs anymore(meaning there are disconnected graphnodes)
		//Pre-conditions: there must be a constructed graph 
		//Post-conditions: a number will be returned
		int findNextGraphNode();

		//---------- UnVisit -----------
		//Unvisits each graphNode
		//Pre-conditions: there must be a constructed graph
		//Post-conditions: the visited field of each graphNode will be false
		void unVisit();
		

		GraphNode data[MAX];//array of graph nodes (max is 100)
		int size;//number of graph nodes 
};