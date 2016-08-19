//Elias Muche 
//5-11-16
//Program 3:My driver 

#include <iostream>
#include <fstream>
#include "graphl.h"
#include "graphm.h"
using namespace std;

int main() {
	////////////// Part 1 ///////////////

	ifstream file("dataUWB.txt");
	if (!file) {
		cout << "File could not be opened." << endl;
		return 1;
	}


	GraphM graph;
	graph.buildGraph(file);
	graph.findShortestPath();
	graph.displayAll();
	for(int i=1;i<=23;i++){
		for(int j=1;j<=23;j++){
			graph.display(i,j);
		}
	}

	ifstream file2("data32.txt");
	if (!file2) {
		cout << "File could not be opened." << endl;
		return 1;
	}
	/////////// End of part 1 //////////////

	
	
	////////// Part 2 ///////////
	GraphL dfsGraph;
	dfsGraph.buildGraph(file2);
	dfsGraph.displayGraph();
	cout<<endl<<"DFS for this graph is   ";
	dfsGraph.depthFirstSearch();

	return 0;
	////////// End of Part 2 ////////////// 



}