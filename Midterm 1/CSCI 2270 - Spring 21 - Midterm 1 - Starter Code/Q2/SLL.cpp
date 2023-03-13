#include <iostream> // predefined header file (defined for you)
using namespace std;

#include "SLL.hpp" // your own header file
// <> vs "" -- compiler looks for the file in the C++ implementation
// vs in the current directory


SLL::SLL(){ // constructor definition
	head = nullptr;
}

SLL::~SLL(){
	Node* crawler;

	while(head!=nullptr){
		crawler = head->next;
		delete head;
		head = crawler;
	}
}


void SLL::displayList(){
	Node* crawler = head;
	while( crawler != nullptr ){
		cout << crawler->key << "->";
		crawler = crawler->next;
	}

	cout << "END" << endl;
}


void SLL::insert(Node* afterMe, char newValue){

	if(head == nullptr){
		// first case: empty list
		// add new node and make head point to it
		head = new Node;
		head->key = newValue;
		head->next = nullptr; // what if we forget this line?
	}
	else if(afterMe == nullptr){
		// This condition implies that the list is not empty, but
		// the caller wants to add node before the head node
		Node* newNode = new Node;
		newNode->key = newValue;
		newNode->next = head;
		head = newNode;
		// at this point, we can test our code for this use case

	}
	else{
		Node* newNode = new Node;
		newNode->key = newValue;
		newNode->next = afterMe->next;
		afterMe->next = newNode;
	}


}

bool SLL::palindrome(){
	Node * temp = head;//Create a new node that is set to head
	if(temp==NULL){//Check if the list is empty
		return true;
	}else if(temp->next==NULL){//Check if the list has only one element 
		return true;
	}else{
		int numElements=0;//Declare a variable to hold the number of elements
		while(temp != NULL){//Loop to find how many elements there are in the list
			numElements++;
			temp=temp->next;
		}
		temp=head;//Set temp back to head
		numElements=numElements-1;
		if(atIndex(0)==atIndex(numElements)&&atIndex(1)==atIndex(numElements-1)){//Check to see if the first and last, and second and second to last elements equal eachother
			return true;
		}else{
			return false;
		}
	}
	return true;
}

char SLL::atIndex(int i){
	Node * temp = head;//Create a new node that is set to head
	for(int index = 0; index<i;index++){//Iterate through the linked list to get to the desired index 
		if(temp==NULL){//Check to make sure i is still a valid index
			cout<<"Index "<<i<<" is a invalid index."<<endl;//If not print error message
			return '\0';//return NULL charecter 
		}else{
			temp=temp->next;//Set temp to the next Node in the list
		}
	}
	return temp->key;//return the charecter of the temp
}



