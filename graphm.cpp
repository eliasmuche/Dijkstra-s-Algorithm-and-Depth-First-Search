//Elias Muche 
//4-20-16
//Program 3 Part 1:Shortest Path

#include "graphm.h"
#include <iostream>
#include <sstream>
#include "limits.h"
#include <cstring>
#include <algorithm>
using namespace std;

	//----------- Default Constructor -----------
	//Sets the distance for each element of T to inifnity 
	//Sets the visited of each element of T to false 
	//Sets the path of each element of T to 0
	//Pre-conditions: none
	//Post-conditions: The members above will be initialized
	GraphM::GraphM(){
		size=0;
		for(int i=0;i<MAXNODES;i++){
			for(int j=0;j<MAXNODES;j++){
				T[i][j].dist=INT_MAX;//initialize the distances 
				T[i][j].visited=false;//initialize visited 
				T[i][j].path=0;//initialize the paths
				
				C[i][j]=INT_MAX;//initialize the costs
			}
		}
		
	}

	//----------- buildGraph ------------
	//Takes in a file object 
	//Reads from a file to create a graph
	//Pre-conditions: the file must be formatted exactly as specified on canvas 
	//Post-conditions: a graph will be created
	void GraphM::buildGraph(istream &in){
		string line;//will store each line
		getline(in,line);//get the first line 
		if(in.eof()){
			return;	
		}
		istringstream ( line ) >> size;//convert the string to an int and store it in size 
		for(int i=1;i<=size;i++){
			getline(in,line);//get the next line
			NodeData vertex(line);
			data[i]=vertex;//store that line into the nodedata array
		}
					
		int row=0;//will store the row 
		int col=0;//will store the column		
		int val=0;//will store the value to place at C[row][col]
		int i=0;//will be used to help find row, col, and val
		getline(in,line);//get the first line of the edge information

		while(line[0]!='0'){
			i=line.find_first_of(" ",0);//location of the first space in the current line
			istringstream(line.substr(0,i))>>row;//store the first number into row 
			
			line=line.substr(i,line.length());//move past the first number
			i=line.find_first_not_of(" ");//find the location where the second number starts
			line=line.substr(i,line.length());//move there
			i=line.find_first_of(" ",0);//location where the next space is in the current line
			istringstream(line.substr(0,i))>>col;//store the second number into col 
			
			line=line.substr(i,line.length());//move past the second number 
			i=line.find_first_not_of(" ");//find the location where the third number starts
			line=line.substr(i,line.length());//move there 
			istringstream(line)>>val;//store the third number into val
					
			insertEdge(row,col,val);
			getline(in,line);

		}
	
		
	} 
	//----------- InsertEdge --------------
	//Takes in two vertices and an edge cost 
	//Inserts an edge at the specified location 
	//Pre-conditions: the vertices must be existent and not equal
	//Post-conditions: An edge will be inserted if the given vertices were existent
	void GraphM::insertEdge(int vertex1, int vertex2, int edgeCost){
		if(vertex1 > size || vertex2 > size){
			return;
		}
		else if(vertex1 < 1 || vertex2 < 1){
			return;
		}
		else if(vertex1 == vertex2){
			return;
		}
		C[vertex1][vertex2]=edgeCost;//place the edge at the specified location
	}
	
	//----------- RemoveEdge --------------
	//Takes in two vertices(int locations)  
	//Removes an edge at the specified location 
	//Pre-conditions: the vertices must be existent 
	//Post-conditions: An edge will be removed if the given vertices were existent
	void GraphM::removeEdge(int vertex1, int vertex2){
		if(vertex1 > size || vertex2 > size){
			return;
		}
		else if(vertex1 < 1 || vertex2 < 1){
			return;
		}
		
		C[vertex1][vertex2]=INT_MAX;//place infinity into the specified edge 
	}

	//---------- FindShortestPath ------------
	//Finds the shortest path from every node to every other node
	//Pre-conditions: the graph must be constructed 
	//Post-conditions: the shortest path and distance from every node to every other node will be stored in T
	void GraphM::findShortestPath(){
		for (int source = 1; source <= size; source++) {
      		T[source][source].dist = 0;
      		//finds the shortest distance from source to all other nodes
			
      		for (int i = 1; i<= size; i++) {
				int v=findV(source);//obtain v 
				if(v==-1){//this means there are no more v's so change the source 
					break;
				}
				T[source][v].visited=true;//mark v visited
           		for(int w=1;w<=size;w++){//for each w of v 
           			if (!T[source][w].visited && C[v][w]!=INT_MAX) {//if it's not visited and there is an edge between v and w
						if(T[source][w].dist>T[source][v].dist+C[v][w]){//if the current distance to w is bigger than the new path's distance
							T[source][w].dist=T[source][v].dist+C[v][w];//set the new distance
							T[source][w].path=v;//mark the park 
						}
	 				
					}	
				
				}
				
				
      		}
		
   		}		

	}	
	
	//--------- DisplayAll -----------
	//Displays the shortest path from each source node to every other node as well as the distance of the path
	//Pre-conditions: none
	//Post-conditions: the shortest path and distance from every node to every other node will be displayed
	void GraphM::displayAll(){
			cout<<"Description     From       To      Dist    Path"<<endl;//header line

		for (int source=1;source<=size;source++){//represents the source 
			cout<<data[source]<<endl;//print the name of the vertex
			for(int destination=1;destination<=size;destination++){//represents the destination
				if(T[source][destination].dist!=INT_MAX && T[source][destination].dist!=0){//if there is an edge and the source is not the destination
					cout<<"\t\t"<<source<<"   "<<destination<<"    "<<T[source][destination].dist<<"    ";
					string path="";
					showPath(source,destination,path);//call the path method for the given source-destination pair
					cout<<destination<<endl;

				}	
				else{//if there's no edge or the source and destination are the same
					cout<<"\t\t"<<source<<"   "<<destination<<"    "<<"---      "<<endl;//don't print a path or a distance
				}
										
				cout<<endl;		
			}
		}	
	}
	
	//----------- Display -----------
	//Displays the shortest path from a given source node to a given destination node as well as the distance of the path
	//Takes in a two ints (the source and the destination)
	//Pre-conditions: none 
	//Post-conditions: the shortest distance and path from the first param to the second param will be displayed
	void GraphM:: display(int source,int destination){
		if(T[source][destination].dist!=INT_MAX && T[source][destination].dist!=0){//if there is an edge and the source is not the destination
			cout<<"\t\t"<<source<<"   "<<destination<<"    "<<T[source][destination].dist<<"    ";
			string tempPath="";
			showPath(source,destination,tempPath);//call the path method for the given source-destination pair
			cout<<destination<<endl;
			tempPath+=destination;
			for(int i=0;i<tempPath.length();i++){
				int node=tempPath[i];
				cout<<data[node]<<endl;

			}
			cout<<endl;

		}	
		else{//if there's no edge or the source and destination are the same
			cout<<"\t\t"<<source<<"   "<<destination<<"    "<<"---      "<<endl;//don't print a path or a distance
		}
				

	}
	
	

	//--------- FindV ----------
	//Utility method
	//finds the shortest unvisited node
	//Pre-conditions: the graph must be constructed 
	//Post-conditions: a number will be returned
	int GraphM::findV(int source){
		int low=INT_MAX;//intialize low
		int v=-1;//variable to be returned
		for(int i=1;i<=size;i++){//for the entire row
			if( T[source][i].dist<low){//if the current v has a lower cost from the given source
				if(!T[source][i].visited){//if this v hasn't been visited
					low=C[source][i];//update the low
					v=i;//update v

				}	
				else{
					continue;

				}
			
			}
		}
		return v;//return v;		
	}

	//---------------   UnMark -----------------
	//Unmarks each cell's visited field
	//Pre-conditions: none
	//Post-conditions: each visited field of each cell will be false
	void GraphM::unMark(){
		for(int i=1;i<=size;i++){//the row
			for(int j=1;j<=size;j++){//the column 
				T[i][j].visited=false;//mark visited false
			}
		}

	}

	//----------- ShowPath -------------
	//Takes two ints, a source, a destination
	//Also takes a string that will contain the path (to be used later in display)
	//Displays the path from the source to the destination
	//Pre-conditions: none
	//Post-conditions: the path from the source to the destination will be printed
	void GraphM::showPath(int source,int destination,string &tempPath){
		if(source!=destination){//if the source and destination are different
			if(T[source][destination].path!=0){//if the path isn't 0
				showPath(source,T[source][destination].path,tempPath);//keep calling until the first number of the path is reached 
				

			}
			cout<<T[source][destination].path<<" ";//print the path
			tempPath+=T[source][destination].path;
		}
		
	}