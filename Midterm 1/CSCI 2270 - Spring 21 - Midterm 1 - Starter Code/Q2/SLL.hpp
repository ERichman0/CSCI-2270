// SLL.hpp - interface file (header file)
#ifndef SLL_H
#define SLL_H

struct Node{
	char key;
	Node *next;
};

class SLL{
private:
	Node* head;

public:
	SLL(); // constructor declaration

	~SLL(); // destructor declaration

	void displayList();
	// Precondition: the head node is defined.

	// Post condition: display the key values of the entire list, starting with
	// first node and ending with last node.

	void insert(Node* afterMe, char newValue);
	// Precondition: afterMe is a valid pointer to a node in the linked list.
	// newValue is a valid string.

	// Postcondition: a new node is created and newValue is stored as its key.
	// The new node is added after node containing afterMe.

	bool palindrome();
	// Precondition: the head node is defined
	
	// Postcondition: if the list constitutes a palindrome, the function returns 
	// a boolean true. Otherwise, it returns a false.

	char atIndex(int i);
	// Precondition: input parameter is a positive integer

	// Postcondition: return a character corresponding to the key value of the 
	// node at the i-th numbered node in the list. The head node is the 0-index node, 
	// the following node is the 1-index node, and so on. 
};





#endif
