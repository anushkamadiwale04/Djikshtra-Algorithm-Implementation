//********************************************************************
// ASU CSE310 Spring 2023 Assignment #7
// Name of Author: Anuhska Madiwale
// ASU ID: 1221561965
// Description: This is the header file that defines a weighted directed graph
//********************************************************************


#include "MinPriorityQueue.h"

using namespace std;

class Graph
{
   private:
   int numOfNode;                 //number of vertices in the graph
   MinPriorityQueue* cityHeap;    //adjacency list of the graph, it is a min-heap
                                  //of departure city objects
   MinPriorityQueue* pathfinal;
   public:
   Graph(int numOfNode, MinPriorityQueue* cityHeap);
   ~Graph();
   void printGraph();
   void initialize_single_source(string sourceCityName);
   void relax(DepCity u, DepCity v);
   int findOneCity(string aCityName);
   void dijkstra(string sourceCityName);
   void printDijkstraPath(string sourceCityName);
   void printPath(string sourceCityName, DepCity* aCity);

   //add any auxiliary functions here in case you need them
   //----
};

//*******************************************************************
//Constructor
Graph::Graph(int numOfNode, MinPriorityQueue* cityHeap)
{
   this->numOfNode = numOfNode;
   this->cityHeap = cityHeap;
   pathfinal = new MinPriorityQueue(numOfNode);
}

//*******************************************************************
//Destructor
Graph::~Graph()
{
   delete [] cityHeap;
   cityHeap = NULL;
   numOfNode = 0;
}

//*******************************************************************
//void printGraph();
//This function prints the graph. It traverse through the vertex list,
//then for each vertex, it print its adjacent list from head to tail.
void Graph::printGraph(){
   cityHeap->printHeap();
}

//According to above class definition, define all functions accordingly
void Graph::initialize_single_source(string sourceCityName)
{
   int size = cityHeap->getSize();
   //initialising all nodes.
   int i = 0;
   while (i<size){
      DepCity curr = cityHeap->getDepCityArr()[i];
      cityHeap->getDepCityArr()[i].d = 30000 + i;
      cityHeap->getDepCityArr()[i].pi = NULL;
      if(curr.depCityName.compare(sourceCityName)==0){
         DepCity d2;
         d2.d = 0;
         cityHeap->decreaseKey(i,d2);
      }
      i++;
   }

}
void Graph::relax(DepCity u, DepCity v) {
  int w = u.arrCityList->findArrCity(v.depCityName)->distance;
   //cout<<"WEIGHT - "<< weight<<endl; 
   if(v.d>u.d+w){
      DepCity D;
      D.d= u.d + w;
      cityHeap->decreaseKey(findOneCity(v.depCityName),D);
      int x = pathfinal->isFound(u.depCityName);
      cityHeap->getDepCityArr()[findOneCity(v.depCityName)].pi = &pathfinal->getDepCityArr()[x];
   }
}


int Graph::findOneCity(string aCityName){
   return cityHeap->isFound(aCityName);
}



void Graph::dijkstra(string sourceCityName){
   initialize_single_source(sourceCityName);
   pathfinal = new MinPriorityQueue(numOfNode);
   while (cityHeap->getSize()>0)
   {
      DepCity now = cityHeap->getHeapMin(); // gets the minimum city distance
      cityHeap->extractHeapMin();            // removes the minimum city from the heap
      pathfinal->insert(now);           //adds completed path to a new min heap
      ArrCity *arrcity = now.arrCityList->getHead(); // gets all the adjacent cities to the dep city
      //cout<<"relaxing for "<<curr.depCityName<<endl;
      while(arrcity!=NULL){
         if(findOneCity(arrcity->arrCityName)!=-1){
         DepCity adj= cityHeap->getDepCityArr()[findOneCity(arrcity->arrCityName)];        
         relax(now,adj);
         }
         arrcity = arrcity->next;
      }          // removes the minimum city from the heap
   }
   cityHeap = pathfinal;
  
}
void Graph::printPath(string sourceCityName, DepCity* city1) {
    string path = "";
    DepCity* current = city1;
    while (current != nullptr) {
        if (current->pi != nullptr) {
            path = "->" + current->depCityName + path;
        } else {
            path = current->depCityName + path;
        }
        current = current->pi;
    }
    cout << path << endl;
}

void Graph::printDijkstraPath(string sourceCityName){
   dijkstra(sourceCityName);
   cout<<"\n\nPrint the Dijkstra algorithm running result\n"<<endl;
   cout<<"Source City: "<<sourceCityName<<"\n"<<endl;
   cout << left;
   cout 
     << setw(14) << "Arrival City"
     << setw(15) << "Shortest Dist."
     << setw(15) << "Shortest Path"<<endl;
   for (int i = 0;i<numOfNode;i++){
      if(cityHeap->getDepCityArr()[i].d<30000){
     cout << left;
     cout 
     << setw(15) << cityHeap->getDepCityArr()[i].depCityName
     << setw(15) << cityHeap->getDepCityArr()[i].d;
     printPath(sourceCityName,&cityHeap->getDepCityArr()[i]);
      }else{
      cout << left;
     cout 
     << setw(15) << cityHeap->getDepCityArr()[i].depCityName
     << setw(15) << "None exist"
     <<setw(15)<<"None exist"<<endl;;
      }
   }
}