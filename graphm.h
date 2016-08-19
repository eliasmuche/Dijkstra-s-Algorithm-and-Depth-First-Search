//Elias Muche 
//4-20-16
//Program 3 Part 1:Shortest Path

#include "nodedata.h"
#include <iostream>
using namespace std;
const int MAXNODES=100;



class GraphM {                           

   public:
	//----------- Default Constructor -----------
	//Sets the distance for each element of T to inifnity 
	//Sets the visited of each element of T to false 
	//Sets the path of each element of T to 0
	//Pre-conditions: none
	//Post-conditions: The members above will be initialized
	GraphM();

	//----------- buildGraph ------------
	//Takes in a file object 
	//Reads from a file to create a graph
	//Pre-conditions: the file must be formatted exactly as specified on canvas 
	//Post-conditions: a graph will be created
	void buildGraph(istream &in);

	//----------- InsertEdge --------------
	//Takes in two vertices and an edge cost 
	//Inserts an edge at the specified location 
	//Pre-conditions: the vertices must be existent and not equal
	//Post-conditions: An edge will be inserted if the given vertices were existent
	void insertEdge(int vertex1, int vertex2, int edgeCost);
	
	//----------- RemoveEdge --------------
	//Takes in two vertices(int locations)  
	//Removes an edge at the specified location 
	//Pre-conditions: the vertices must be existent 
	//Post-conditions: An edge will be removed if the given vertices were existent
	void removeEdge(int vertex1, int vertex2);
	
	//---------- FindShortestPath ------------
	//Finds the shortest path from every node to every other node
	//Pre-conditions: the graph must be constructed 
	//Post-conditions: the shortest path and distance from every node to every other node will be stored in T
	void findShortestPath();

	//--------- DisplayAll -----------
	//Displays the shortest path from each source node to every other node as well as the distance of the path
	//Pre-conditions: none
	//Post-conditions: the shortest path and distance from every node to every other node will be displayed
	void displayAll();

	//----------- Display -----------
	//Displays the shortest path from a given source node to a given destination node as well as the distance of the path
	//Takes in a two ints (the source and the destination)
	//Pre-conditions: none 
	//Post-conditions: the shortest distance and path from the first param to the second param will be displayed
	void display(int source,int destination);
		

      

   private:
	   struct TableType {

         bool visited;          // whether node has been visited

         int dist;              // shortest distance from source known so far

         int path;              // previous node in path of min dist

      };
	  

      NodeData data[MAXNODES];              // data for graph nodes

      int C[MAXNODES][MAXNODES];            // Cost array, the adjacency matrix

      int size;                             // number of nodes in the graph

      TableType T[MAXNODES][MAXNODES];      // stores visited, distance, path

	//--------- FindV ----------
	//Utility method
	//finds the shortest unvisited node
	//Pre-conditions: the graph must be constructed 
	//Post-conditions: a number will be returned
   	int findV(int source);

	//---------------   UnMark -----------------
	//Unmarks each cell's visited field
	//Pre-conditions: none
	//Post-conditions: each visited field of each cell will be false
	void unMark();

	//----------- ShowPath -------------
	//Takes two ints, a source, a destination
	//Also takes a string that will contain the path (to be used later in display)
	//Displays the path from the source to the destination
	//Pre-conditions: none
	//Post-conditions: the path from the source to the destination will be printed
    void showPath(int source, int destination,string &tempPath); 

};



