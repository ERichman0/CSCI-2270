#include <iostream>
#include <fstream>
#include "MovieTree.hpp"

using namespace std;

void destroyTree(TreeNode *root){
	if(root==NULL){
		return;
	}
	destroyTree(root->leftChild);
	destroyTree(root->rightChild);
	LLMovieNode* temp=root->head;
	while(temp->next != NULL){
		LLMovieNode* deleter=temp;
		temp=temp->next;
		delete deleter;
	}
	delete temp;
	delete root;
}

MovieTree::~MovieTree(){
	destroyTree(root);
}

LLMovieNode* getLLMovieNode(int r, std::string t, int y, float q)
{
	LLMovieNode* lmn =new LLMovieNode();
	lmn->ranking = r;
	lmn->title=t;
	lmn->year =y;
	lmn->rating =q;
	lmn->next =NULL;
	return lmn;
}

/* ------------------------------------------------------ */
MovieTree::MovieTree()
{
	root = NULL;
}

/* ------------------------------------------------------ */
void inorderTraversalHelper(TreeNode * root) {
		if (root == NULL) {
			return;
		}

		inorderTraversalHelper(root->leftChild);
		cout << root->titleChar << " ";
		inorderTraversalHelper(root->rightChild);
}

void MovieTree::inorderTraversal() {
	inorderTraversalHelper(root);
	cout << endl;
}

/* ------------------------------------------------------ */
TreeNode* searchCharHelper(TreeNode* curr, char key)
{
    if (curr == NULL)
        return curr;
    else if(curr->titleChar == key)
        return curr;
    else if (curr->titleChar > key)
        return searchCharHelper(curr->leftChild, key);
    else
        return searchCharHelper(curr->rightChild, key);
}

TreeNode* MovieTree::searchCharNode(char key)
{
    return searchCharHelper(root, key);
}

/* ------------------------------------------------------ */

void showMovieCollectionHelper(TreeNode* curr){
	if(curr != NULL){
		showMovieCollectionHelper(curr->leftChild);
		LLMovieNode* temp = curr->head;
		cout<<"Movies starting with letter: "<<curr->titleChar<<endl;
		while(temp != NULL){
			cout<<" >> "<<temp->title<<" "<<temp->rating<<endl;
			temp=temp->next;
		}
		showMovieCollectionHelper(curr->rightChild);
	}
	return;
}

void MovieTree::showMovieCollection(){
	showMovieCollectionHelper(root);
	return;
}

TreeNode* addMovieHelper(TreeNode* &t, TreeNode* newNode){
	if(t==NULL){
		return newNode;
	}
	if(newNode->titleChar<t->titleChar){
		TreeNode* leftNode = addMovieHelper(t->rightChild,newNode);
		t->leftChild=leftNode;
		leftNode->parent=t;
	}else if(newNode->titleChar>t->titleChar){
		TreeNode *rightNode=addMovieHelper(t->rightChild,newNode);
		t->rightChild=rightNode;
		rightNode->parent=t;
	}else if(newNode->titleChar==t->titleChar){
		LLMovieNode* nodeToInsert=newNode->head;
		LLMovieNode* curr=t->head;
		LLMovieNode* prev=NULL;
		while(curr!=NULL&&curr->title.compare(nodeToInsert->title)<0){
			prev=curr;
			curr=curr->next;
		}
		if(curr!=NULL&&curr->title.compare(nodeToInsert->title)==0){
			return t;
		}else{
			if(prev==NULL){
				nodeToInsert->next=t->head;
				t->head=nodeToInsert;
			}else if(curr==NULL){
				prev->next=nodeToInsert;
			}else{
				prev->next=nodeToInsert;
				nodeToInsert->next=curr;
			}
		}
	}
	return t;
}

void insertLinked(TreeNode* T, LLMovieNode* newNode){
	LLMovieNode* tempNode = T->head;
	if(newNode->title.compare(tempNode->title)<0){
		newNode->next=tempNode;
		T->head=newNode;
		return;
	}
	while(tempNode->next != NULL){
		if(newNode->title.compare((tempNode->next)->title)<0){
			newNode->next=tempNode->next;
			tempNode->next=newNode;
			return;
		}else{
			tempNode=tempNode->next;
		}
	}
	tempNode->next=newNode;
	return;
}

TreeNode* insertTree(TreeNode* T, LLMovieNode* newNode){
	if(T==NULL){
		TreeNode* tempNode=new TreeNode();
		tempNode->head=newNode;
		tempNode->titleChar=newNode->title[0];
		T=tempNode;
		T->parent=NULL;
	}else if(newNode->title[0]==T->titleChar){
		insertLinked(T,newNode);
	}else if(newNode->title[0]<T->titleChar){
		T->leftChild=insertTree(T->leftChild,newNode);
		T->leftChild->parent=T;
	}else{
		T->rightChild=insertTree(T->rightChild, newNode);
		T->rightChild->parent=T;
	}
	return T;
}

void MovieTree::insertMovie(int ranking, string title,int year, float rating){
	LLMovieNode* newNode=getLLMovieNode(ranking,title,year,rating);
	root=insertTree(root,newNode);
}

void MovieTree::removeMovieRecord(string title){
	TreeNode *T = searchCharHelper(root,title[0]);
	if(T==NULL){
		cout<<"Movie not found."<<endl;
		return;
	}

	LLMovieNode* M = T->head;
	LLMovieNode* temp = M;

	if(M != NULL && M->title == title){
		T->head = M->next;
		delete M;
		return;
	}
	//traverse through linked list
	while(M != NULL && M->title != title){
		temp=M;
		M=M->next;
	}
	if(M==NULL){
		cout<<"Movie not found."<<endl;
	}
	temp->next=M->next;
	delete M;
}

void MovieTree::leftRotation(TreeNode* curr){
	TreeNode* right = curr->rightChild;

	if(curr->titleChar == root->titleChar){
		curr->rightChild=right->leftChild;
		right->leftChild=curr;
		right->parent=NULL;
		curr->parent=right;
		if(curr->rightChild != NULL){
			curr->rightChild->parent=curr;
		}
		root=right;
		return;
	}

	if(curr->parent->rightChild->titleChar == curr->titleChar){
		curr->parent->rightChild=right;
	}else{
		curr->parent->leftChild=right;
	}
	right->parent=curr->parent;
	curr->parent=right;
	curr->rightChild=right->leftChild;
	if(right->leftChild != NULL){
		right->leftChild->parent = curr;
	}
	right->leftChild=curr;
}