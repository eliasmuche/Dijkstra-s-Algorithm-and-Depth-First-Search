//Elias Muche
//5-6-16
//Program 3 Part 2: DFS

#include "graphl.h"	

	//--------- Default Constructor ------------
	//Initializes size
	//Pre-conditions: none 
	//Post-conditions: size will be 0
	GraphL::GraphL(){
		size=0;
	}
	
	//-------- Destructor ---------
	//De-allocates all pointers (nodedatas and edgenodes)
	//Pre-conditions: none
	//Post-conditions: there will be no memory leaks(all dynamically allocated objects will be de-allocated)
	GraphL::~GraphL(){
		for(int i=1;i<=size;i++){//for each graph node
			if(data[i].data!=NULL){//to prevent errors in valgrind
				delete data[i].data;//delete the nodedata 
				data[i].data=NULL;//set it to null
				clearList(data[i].edgeHead);//delete the adjacent nodes of the current graphnode
			}
		}

	}
	
	//---------- BuildGraph -------------
	//Takes in a text file and builds a graph based on the text 
	//Pre-conditions: the file must be formatting exactly as shown on canvas 
	//Post-conditions: a graph will be built assuming the pre-conditions were met
	void GraphL::buildGraph(istream &in){
		string line;
		
		getline(in,line);//read the first line 
		if(in.eof()){
			return;
		}	
		istringstream(line)>>size;//store the number into size
		
		for(int i=1;i<=size;i++){
			getline(in,line);//grab each node line
			GraphNode source;//create a GraphNode object 
			source.data=new NodeData(line);//set the data field 
			data[i]=source;//store it into the array
			data[i].visited=false;//initialize the visited field

		}
		int source;
		int adjacent;
		int i;
		getline(in,line);
		
		while(line[0]!='0'){
			i=line.find_first_of(" ",0);//location of the first space in the current line
			istringstream(line.substr(0,i))>>source;//store the first number into source

			line=line.substr(i,line.length());//move past the first number
			i=line.find_first_not_of(" ");//find the location where the second number starts
			line=line.substr(i,line.length());//move there
			i=line.find_first_of(" ",0);//location where the next space is in the current line
			istringstream(line.substr(0,i))>>adjacent;//store the second number into adjacent
			

			if(data[source].edgeHead==NULL){//if there's no list for the current GraphNode
				data[source].edgeHead=new EdgeNode;//create a new list 
				data[source].edgeHead->adjGraphNode=adjacent;//set the first adjacent node value
			}
			else{//if there's already a list 
				EdgeNode *newEdge=new EdgeNode;//create a new adjacent node 
				newEdge->adjGraphNode=adjacent;//creat a new adjacent node
				newEdge->nextEdge=data[source].edgeHead;//add it to the beginning of the list
				data[source].edgeHead=newEdge;//move head to the newly created adjacent node
				newEdge=NULL;//memory leaks
			}
			getline(in,line);//move on to the next line
			

		}
				
	}

	//----------- DisplayList --------------
	//Displays the adjacent nodes of a given graph node
	//Pre-conditions: there must be a constructed graph 
	//Post-condtions: all of the adjacent nodes of the graph node will be displayed 
	void GraphL::displayList(int source, EdgeNode *edgeNode){
		if(edgeNode==NULL){//stop when the end of the list is reached 
			return;
		}
		cout<<"\tedge "<<source<<" "<<edgeNode->adjGraphNode<<endl<<endl;//print the edge
		displayList(source,edgeNode->nextEdge);//move on to the next edge
	}

	//-------- DisplayGraph ---------
	//Displays the adjacency list as a representation of the graph
	//Pre-conditions: there must be a constructed graph
	//Post-conditions: the list will be displayed
	void GraphL::displayGraph(){
		for(int source=1;source<=size;source++){//for each graph node
			cout<<"Node "<<source<<"   "<<*data[source].data<<endl<<endl;//print out the graphnode
			displayList(source,data[source].edgeHead);//print out its list
		}	
		depthFirstSearch();//display the dfs
		
	}

	//--------- ClearList -----------
	//Takes in an Edge(head of the list) the entire list 
	//Pre-conditions: there must be a constructed graph
	//Post-conditions: the list will be deleted
	void GraphL::clearList(EdgeNode *&edgeNode){
		if(edgeNode==NULL){//stop if the end of the list is reached
			return;
		}
		clearList(edgeNode->nextEdge);//go to the end of the list
		delete edgeNode;//delete the node 
		edgeNode=NULL;//set it to null
	}
	
	//--------- AllVisited ----------
	//Checks if every graphnode has been visited
	//Pre-conditions: there must be a constructed graph
	//Post-conditions: true or false will be returned
	bool GraphL:: allVisited(){
		for(int i=1;i<=size;i++){//for every graph node
			if(!data[i].visited){//if there's an unvisited node 
				return false;//return false
			}
		}
		return true;//everything has been visited at this point
	}

	//---------- NextAdjNode -----------
	//Takes an int(represents a graphnode) and checks to see if a specific graphnode has any more adjacent nodes to visit
	//Also takes another int (represents an adjacent node) that is passed by reference. It will store the next adj node if there's one
	//Pre-conditions: there must be a constructed graph
	//Post-conditions: returns true if there's another unvisited graph node, false if they have all been visited
	bool GraphL::nextAdjNode(int graphNode,int &adjacent){
		
		EdgeNode *temp=data[graphNode].edgeHead;//start at the head list corresponding to the graph node
		while (temp!=NULL){//while the end of the list hasn't been reached
			if(!data[temp->adjGraphNode].visited){//if the current adj node hasn't been visited 
				adjacent=temp->adjGraphNode;//save the node into the second param 
				temp=NULL;//memory leaks 
				return true;//return success 
			}
			else{//otherwise move forward in the list
				temp=temp->nextEdge;
			}
		}
		temp=NULL;//memory leaks
		return false;//at this point there are no more adj nodes so stop and return failure 
	}
	
	//----------- FindNextGraphNode -------------
	//Finds the next unvisited graphnode
	//Will only be called if we can't dfs anymore(meaning there are disconnected graphnodes)
	//Pre-conditions: there must be a constructed graph 
	//Post-conditions: none
	int GraphL:: findNextGraphNode(){
		for(int i=1;i<=size;i++){//for every graph node
			if(data[i].visited){//if the current graph node has been visited
				int next=0;//will store the adj node if there's one 
				bool foundNext=nextAdjNode(i,next);//check if there's adj node
					if(foundNext){//if it was found 
						return next;//return it
				
					}
			}
			else if(!data[i].visited){//if the graph node hasn't been visited
				return i;//return it
			}
		}
		return 0;//at this point there are no more graph nodes so stop
	}
	
	//---------- UnVisit -----------
	//Unvisits each graphNode
	//Pre-conditions: there must be a constructed graph
	//Post-conditions: the visited field of each graphNode will be false
	void GraphL::unVisit(){
		for(int i=1;i<=size;i++){//for every graph node
			data[i].visited=false;//unvisit it
		}

	}
	//---------- DepthFirstSearch ----------
	//Does a depth first search
	//Pre-conditions: there must be a graph to search 
	//Post-conditions: the DFS order will be displayed
	void GraphL::depthFirstSearch(){
		unVisit();//unvisit  every node in case the method was called previously
		int gNode=1;//start at the first node
		int next;//stores the next adjacent node
		bool foundNext;//if the next adjacent node was found 
		stack<int> myStack;//create a stack
		myStack.push(gNode);//push the first node onto the stack 
		data[1].visited=true;//mark it visited 
		cout<<gNode<<"  ";//print it 

		while(true){//keep going 
			while(!myStack.empty()){//while the stack isn't empty 
				foundNext=nextAdjNode(gNode,next);//look for the next adjacent node of the top of the stack
				if(foundNext){//if the next adjacent node was found 
					cout<<next<<"  "; //print it 
					gNode=next;//it becomes the new graph node to examine 
					data[gNode].visited=true;//mark it visited 
					myStack.push(gNode);//push it onto the stack
				}
				else if(!foundNext){//if there's no adjacent node
					myStack.pop();//pop the graph node off of the stack 
					if(!myStack.empty()){//if the stack isn't empty 
						gNode=myStack.top();//the new graph node is the top of the stack 

					}
					
				}
			}
			//at this point, the stack was empty 
			if(allVisited()){//if every node was visited 
				cout<<endl;//print a new line 
				return;//stop 
			}
			//at this point there are still unvisited nodes
			gNode=findNextGraphNode();//find the next unvisited graph node
			myStack.push(gNode);//push it onto the stack 
			cout<<gNode<<"  ";//print it 
			data[gNode].visited=true;//mark it visited
			//the dfs search continues with the new graph node 
		}

	}
