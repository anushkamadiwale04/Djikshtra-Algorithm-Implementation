//********************************************************************
// ASU CSE310 Spring 2023 Assignment #7
// Name: Anushka Madiwale
// ASU ID: 1221561965
// Description: //---- is where you should add your own code
//********************************************************************

#include "Graph.h"
#include <string>
#include <sstream>
using namespace std;

void getCityInfo(string oneLine, string& depCityName, ArrivalCityList* arrCityList);
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, int& distance);     //**optional

int main()
{
   int measure;       //a variable for number of nodes
   string oneLine, sourceCityName;
   string answer = "yes";       //a variable to decide whether to run Dijkstra multiple times
   string dc;
   
   //cout << "Enter number of cities: ";
   cin >> measure;
   cin.ignore(20, '\n');

   //For each line of the file, we will create an ArrivalCityList(which is a linked list)
   //for a specific departure city. It represents all its reachable arrival cities with distance info.
   //Here we use an array of DepCity to store them
   DepCity* depCityArr = new DepCity[measure];

   //Initialize depCityArr. Set each node's d value to be very large 10000
   //initialize each arrival city list
   for(int i = 0; i< measure; i++)
   {
      depCityArr[i].d = 10000 + i;      //***this is to make sure each node has different d value
      depCityArr[i].arrCityList = new ArrivalCityList();
   }

   //get input line by line and create the depCityArr
   for(int i = 0; i< measure; i++)
   {  
         getline(cin, oneLine);
         string delimiter = ",";

         int pos=oneLine.find(delimiter);
         string token = oneLine.substr(0,pos);
         dc = token;
         depCityArr[i].depCityName = dc;
         oneLine.erase(0, pos+delimiter.length());
         
         while(oneLine.length()>1){
         pos=oneLine.find("(");
         string name = oneLine.substr(0,pos);
         oneLine.erase(0, pos+1);
         pos=oneLine.find(",");
         token = oneLine.substr(0,pos-1);
         int dist = stoi(token);
         //cout<<dist<<endl;
         oneLine.erase(0, pos+1);
         depCityArr[i].arrCityList->addArrCity(name,dist);
         }     
   }

  //create a Graph object
  MinPriorityQueue *list = new MinPriorityQueue(measure);
   for (int i=0;i<measure; i++){
      list->insert(depCityArr[i]);
  }

   Graph *path = new Graph(measure,list);

   //print the graph adjacency list before running Dijkstra algorithm
   cout << "\nPrint the graph adjacency list before running Dijkstra algorithm" << endl;
   path->printGraph();
   //Next you need to design a sentinel value controlled while loop base on answer
   //If user answer is 'yes', get source city name, run Dijkstra algorithm, print
   //shortest path, then ask whether user want to continue or not...
bool continueProgram = true;
while (continueProgram) {
    cout << "\nEnter source city name: " << endl;
    getline(cin, sourceCityName);

   int index1 = path->findOneCity(sourceCityName); // Find the index of the first source city
    //cout<<index1;
   if (index1 >= 0) {
    path->printDijkstraPath(sourceCityName); // Print the path for the first source city

    // Check if there is another source city with the same "d" value
    for (int i = 0; i < list->getSize(); i++) {
        if (list->getDepCityArr()[i].d == list->getDepCityArr()[index1].d &&
            list->getDepCityArr()[i].depCityName != sourceCityName) {
            
            // Print the path for the other source city with the same "d" value
            path->printDijkstraPath(list->getDepCityArr()[i].depCityName);
            break;
        }
    }
}
    else {
        cout << sourceCityName << " does NOT exist" << endl;
    }

    cout << "\nFind shortest path for another departure city(yes or no): " << endl;
    getline(cin, answer);
    continueProgram = (answer.compare("yes") == 0);
}

cout << "\nProgram terminate" << endl;
}

//************************************************************************
//Give one line in input file, this function extract tokens and get departure city
//name and its arrival cities info.
void getCityInfo(string oneLine, string& depCityName, ArrivalCityList* arrCityList)
{
   string delimiter = ",";

         int pos=oneLine.find(delimiter);
         string token = oneLine.substr(0,pos);
         depCityName = token;
         cout<< depCityName<<endl;
         oneLine.erase(0, pos+delimiter.length());

         while(oneLine.length()>1){
         pos=oneLine.find("(");
         string name = oneLine.substr(0,pos);
         cout<<name<<endl;
         oneLine.erase(0, pos+1);
         pos=oneLine.find(")");
         token = oneLine.substr(0,pos);
         int dist = stoi(token);
         cout<<dist<<endl;
         oneLine.erase(0, pos+2);
}
}

//****************************************************************************
//Given one arrival city info. format of, such as Z(60), this function
//extract arrival city name 'Z' and distance 60 from it.
//this function is optional. Feel free to extract tokens using your own way
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, int& distance)
{
   std::istringstream iss(oneArrCityInfo);
    std::getline(iss, arrCityName, '(');
    iss >> distance;
}