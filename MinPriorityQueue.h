//********************************************************************
// ASU CSE310 Spring 2023 Assignment #7
// Name of Author: Anushka Madiwale
// ASU ID: 1221561965
// Description: //---- is where you should add your own code
//********************************************************************

#include "ArrivalCityList.h"


using namespace std;

//Each node of the graph which is a departure City
struct DepCity
{
    string depCityName;
    int d;
    struct DepCity* pi;
    ArrivalCityList* arrCityList;
};

//class MinPriorityQueue represents a Min-heap that contains DepCity objects.
//The key of each DepCity is its d value.
class MinPriorityQueue
{
    private:
        struct DepCity* depCityArr;	        //a DepCity array
        int capacity, size;

	public:
        MinPriorityQueue(int capacity);//
        ~MinPriorityQueue();//

        DepCity* getDepCityArr();//
        int getSize();//
        int getCapacity();//
        int isFound(string oneDepCityName);//
        bool decreaseKey(int index, DepCity oneDepCityWithNewDValue);//
        bool insert(DepCity oneDepCity);//
        void heapify(int index);
        DepCity getHeapMin();//
        void extractHeapMin();//
        int leftChild(int parentIndex);//
        int rightChild(int parentIndex);//
        int parent(int childIndex);//
        void printHeap();
        void build_min_heap();
        void checkEmptyList();//
        void doubleheap();
};
MinPriorityQueue::MinPriorityQueue(int capacity)
{
    this->size = 0;
    this->depCityArr = new DepCity[capacity];
    this->capacity = capacity;
}

MinPriorityQueue::~MinPriorityQueue()
{
    for (int i = 0; i < size; i++) {
        depCityArr[i].~DepCity();
    }
    delete[] depCityArr;
}
DepCity* MinPriorityQueue::getDepCityArr()
{
    return depCityArr;
}

int MinPriorityQueue::getSize()
{
    return size;
}

int MinPriorityQueue::getCapacity()
{
    return capacity;
}
int MinPriorityQueue::leftChild(int parentIndex)     //gets the left child
{
    int lchild = (2 * parentIndex) + 1;
    //cout<<lchild;
    return lchild;
    
}
int MinPriorityQueue::rightChild(int parentIndex)        //gets the right child 
{
    int rchild = (2 * parentIndex) + 2;
    //cout<<rchild;
    return rchild;
    
}
int MinPriorityQueue::parent(int childIndex)     //gets the parent at index
{
    int p = (childIndex - 1) / 2;
    return p;
}     
int MinPriorityQueue::isFound(string oneDepCityName)
{
    int index = 0;
	while(index < size){
		if(depCityArr[index].depCityName.compare(oneDepCityName)==0){
		return index;
		}
		index++;
		}
	return -1;
}  
DepCity MinPriorityQueue::getHeapMin()
{
    checkEmptyList();       //checks if list is empty
    return depCityArr[0];  //get first element of heap since it the min
}
void MinPriorityQueue::extractHeapMin()
{
    checkEmptyList();       //checks if list is empty
    // replace root with last element
    depCityArr[0] = depCityArr[size-1];
    // decrease size
    size--;
    // float down the new root to maintain min heap property
    heapify(0);
}
bool MinPriorityQueue::decreaseKey(int index, DepCity oneDepCityWithNewDValue) {
    if (index > size || depCityArr[index].d < oneDepCityWithNewDValue.d) {
        return false;
    }
    depCityArr[index].d = oneDepCityWithNewDValue.d;
    while (index > 0 && depCityArr[parent(index)].d > depCityArr[index].d) {
        std::swap(depCityArr[index], depCityArr[parent(index)]);
        index = parent(index);
    }
    return true;
}
void MinPriorityQueue::heapify(int index) {
    int ind = index;
    int left = leftChild(index);
    int right = rightChild(index);
    
    if (left < size && depCityArr[left].d < depCityArr[ind].d) {
        ind = left;
    }
    if (right < size && depCityArr[right].d < depCityArr[ind].d) {
        ind = right;
    }
    if (ind != index) {
        std::swap(depCityArr[index], depCityArr[ind]);
        heapify(ind);
    }
}

void MinPriorityQueue::build_min_heap() {
    int half = (size / 2);
    for (int i =  half - 1; i >= 0; i--) {
        heapify(i);
    }
}
//*********************************************************
void MinPriorityQueue::printHeap()
{
	if(size != 0){
		cout<<"Heap size = "<<size<<"\n"<<endl;
	    cout << left;
        cout << setw(15) << "Dep. City"
        << setw(12) << "d Value"
        << setw(15) << "PI"
        << "Arrival City List" << endl;
        int i = 0;
        while (i < size){
        cout << left;
        cout << setw(15) << depCityArr[i].depCityName
        << setw(12) << depCityArr[i].d;
	    if(depCityArr[i].pi == nullptr){
		    cout<<setw(15) << "No Parent";        
	    }
	    else{
            cout<< setw(15) << depCityArr[i].pi->depCityName;
	    }
        depCityArr[i].arrCityList->printArrCityList();
        i++;
        }
	}
	else{
        checkEmptyList();
    }
}
void MinPriorityQueue::doubleheap(){
// check if heap is at capacity and resize if necessary
    if (size >= capacity) { 
        capacity *= 2;          //doubles the capacity
        DepCity* temp = new DepCity[capacity];
        for (int i = 0; i < size; i++) {
            temp[i] = depCityArr[i];
        }
        delete [] depCityArr;
        depCityArr = temp;
        cout << "\nReach the capacity limit, double the capacity now." << endl;
        //cout << "\nThe new capacity now is " << capacity << endl;
    }
}
//************************************************************
//when you create the dummy node, initialize its d value to be
//30000 which represents infinite
bool MinPriorityQueue::insert(DepCity oneDepCity)
{   
    // check if the employee ID already exists in the heap
    for (int i = 0; i < size; i++) {
        if (depCityArr[i].depCityName.compare(oneDepCity.depCityName) == 0) {
            //cout << "\nDuplicated City. Not added" << endl;
            return false;
        }
    }
    if(isFound(oneDepCity.depCityName)!= -1){
		return false;
	}
	doubleheap();
	DepCity newD;
	newD.d = 30000;
	newD.pi = oneDepCity.pi;
    newD.arrCityList = oneDepCity.arrCityList;
	newD.depCityName = oneDepCity.depCityName;
	depCityArr[size] = newD;
	size++;
	bool success = decreaseKey(size-1,oneDepCity);
	return true;
}

//According to above class definition, define all other functions accordingly
void MinPriorityQueue::checkEmptyList()      //check if list is empty
{
    if (size == 0)
    {
        cout << "Empty heap, no elements" << endl;
        return;
    }
}