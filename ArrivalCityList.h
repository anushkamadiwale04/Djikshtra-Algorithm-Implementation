//********************************************************************
// ASU CSE310 Spring 2023 Assignment #7
// Name of Author: Anushka Madiwale
// ASU ID: 1221561965
// Description: //---- is where you should add your own code
//********************************************************************

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
//struct ArrCity represents an arrival city information with
//distance info. from a specific departure city
struct ArrCity
{
    string arrCityName;
    int distance;
    struct ArrCity* next;
};

//class ArrivalCityList is a linked list of ArrCity
class ArrivalCityList
{
    private:
        struct ArrCity* head;

    public:
        ArrivalCityList();
        ~ArrivalCityList();
        ArrCity* getHead();
        ArrCity* findArrCity(string oneCity);
        bool addArrCity(string oneCity, int distance);
        ArrCity* findInsertionPoint(string oneCity);
        void printArrCityList();
        void emptyarrlist();
};

ArrivalCityList::ArrivalCityList(){
    head = nullptr;
}
ArrivalCityList::~ArrivalCityList(){
     // Add your own code
     int count= 0;
    struct ArrCity* current = head;
    for (int i = 0; current != nullptr; i++) {
        struct ArrCity* temp = current;
        current = current->next;
        count++;
        delete temp;
    }
}
ArrCity* ArrivalCityList::getHead() {
    return head;
}
//*******************************************************************
//ArrCity* findArrCity(string oneCity);
//A function to find whether the parameterized city is inside the LinkedList or not.
//returns a pointer that points to the city if it exist, otherwise return NULL
ArrCity* ArrivalCityList::findArrCity(string oneCity) {
    ArrCity* current = head;
    while(current!= nullptr){
        if(current->arrCityName.compare(oneCity)==0){
            return current;
        }
        current = current->next;
    }
    return current;
}
//*******************************************************************
//bool addArrCity(string oneCity, int distance);
//Creates a new ArrCity and inserts it into the list at the right place.
//It also maintains an alphabetical ordering of the ArrCities while inserting
//it into the list. Note: you cannot insert duplicated ArrCity
//Return value: true if it is successfully inserted and false in case of failures.
bool ArrivalCityList::addArrCity(string oneCity, int distance) {
    if (findArrCity(oneCity) != NULL) {
        return false;
    }

    ArrCity* addCar = new ArrCity;
    addCar->arrCityName = oneCity;
    addCar->distance = distance;

    ArrCity* insertBefore = findInsertionPoint(oneCity);
    if (insertBefore == NULL) {
        addCar->next = head;
        head = addCar;
    } else {
        addCar->next = insertBefore->next;
        insertBefore->next = addCar;
    }

    return true;
}

ArrCity* ArrivalCityList::findInsertionPoint(string oneCity) {
    ArrCity* current = head;
    ArrCity* prev = NULL;

    while (current != NULL && current->arrCityName.compare(oneCity) < 0) {
        prev = current;
        current = current->next;
    }
    return prev;
}


//According to above class definition, define all functions accordingly
void ArrivalCityList::printArrCityList() {
    if(head != nullptr){
        ArrCity *temp = head;
      while(temp != NULL)
      {
         cout  
              << temp->arrCityName<<"("
              << temp->distance<<"),";
         temp = temp->next;
      }
      cout<<endl;
    }
   else
   {
      emptyarrlist();
   }
}
void ArrivalCityList::emptyarrlist(){
    if(head == NULL)
   {
   	cout<<"Arrival city list is empty"<<endl;
   }
}
