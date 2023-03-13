#include <iostream>
#include "bst.hpp"

BST::BST() {
	root = NULL;
}

BST::~BST() {
	deleteTree(root);
	root = NULL;
}
void BST::deleteTree(Node* node) {
	if (node != NULL) {
		deleteTree(node->leftChild);
		deleteTree(node->rightChild);
		delete node;
	}
}

/*
** Implement the following function to return the count of comparisons, 
**   you may implement helper functions.
*/

int searchCounterHelper(Node *search, int target){
	int count=0;
	while(search != nullptr){
		if(search->key>target){
			count++;
			search=search->leftChild;
		}
		if(search->key<target){
			count++;
			search=search->rightChild;
		}else if(search->key==target){
			count++;
			break;
		}
	}
	return count;
}

int BST::searchCounter(int target) {
	int counter=0;
	return searchCounterHelper(root,target);
}
