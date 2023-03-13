#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Helper function: Create new node using provided args
MovieNode* getMovieNode(int rank, string t, int y, float r) {
    MovieNode* nn = new MovieNode;
    nn->title = t;
    nn->ranking = rank;
    nn->year = y;
    nn->rating = r;
    return nn;
}

MovieTree::MovieTree() {
  root=NULL;
}

void _destruct(MovieNode * &T){
  if(T==0){//base case
    return;
  }else{//inductive case
    _destruct(T->left);
    _destruct(T->right);
    delete T;
    T = NULL;
  }
}

MovieTree::~MovieTree() {
  _destruct(root);
}


void printMovie(MovieNode* &T){
  if(T == NULL){
    return;
  }else{
    printMovie(T->left);
    cout<<"Movie: "<<T->title<<" ("<<T->rating<<")"<<endl;
    printMovie(T->right);
  }
}

void MovieTree::printMovieInventory() {
  if(root == NULL){
    cout<<"Tree is empty. Cannot print."<<endl;
  }else{
    printMovie(root);
  }
}

void MovieTree::addMovieNode(int ranking, string title, int year, float rating) {
  MovieNode * newNode = new MovieNode;
  newNode->ranking=ranking;
  newNode->title=title;
  newNode->year=year;
  newNode->rating=rating;
  MovieNode *curr = root;
  MovieNode *prev;
  
  if(root==NULL){
    root=newNode;
  }else{
    while(curr != NULL){
      prev = curr;
      if(newNode->title.compare(curr->title)<0){
        curr=curr->left;
      }else if(newNode->title.compare(curr->title)>0){
        curr=curr->right;
      }
    }
    if(newNode->title.compare(prev->title)<0){
      prev->left=newNode;
    }else if(newNode->title.compare(prev->title)>0){
      prev->right=newNode;
    }
  }
}

void MovieTree::findMovie(string title) {
  MovieNode *temp = root;
  if(temp == NULL){
    return;
  }else{
    while(temp != 0){
      if(title==temp->title){
        cout<<"Movie Info:"<<endl;
        cout<<"=================="<<endl;
        cout<<"Ranking:"<< temp->ranking <<endl;
        cout<<"Title  :"<< temp->title <<endl;
        cout<<"Year   :"<< temp->year <<endl;
        cout<<"Rating :"<< temp->rating <<endl;
        return;
      }else if(title.compare(temp->title)>0){
        temp=temp->right;
      }else{
        temp=temp->left;
      }
    }
    cout<<"Movie not found."<<endl;
  }
}

void findItem(MovieNode *n, int year, float rating, int &h){
  if(h==0){
    cout<<"Movies that came out after "<<year<<" with rating at least "<<rating<<":"<<endl;
    h++;
  }

  if(n->year > year && n->rating >= rating){
    cout<<n->title<<" ("<<n->year<<") "<<n->rating<<endl;
  }
  if(n->left != NULL){
    findItem(n->left,year,rating,h);
  }

  if(n->right != NULL){
    findItem(n->right, year, rating , h);
  }
}

void MovieTree::queryMovies(float rating, int year) {
  MovieNode *temp = root;
  int h=0;
  findItem(temp, year, rating, h);
  if(h==0){
    cout<<"Tree is Empty. Cannot query Movies."<<endl;
  }
}

double sumNodes(MovieNode *node)
{
  if(node == NULL){
    return 0;
  }else{
    return sumNodes(node->left)+sumNodes(node->right)+node->rating;
  }
}

double numNodes(MovieNode *node){
  if(node == NULL){
    return 0;
  }else{
    return numNodes(node->left)+ numNodes(node->right)+1;
  }
}

void MovieTree::averageRating() {
  if(root==NULL){
    cout<<"Average rating:0.0"<<endl;
  }else{
    double avg;
    avg = sumNodes(root);
    double numElements;
    numElements=numNodes(root);
    avg= avg/numElements;
    cout<<"Average rating:"<<avg<<endl;
    }
}

void printNodesHelper(MovieNode *node, int level){
  if(node==NULL){
    return;
  }
  if(level==0){
    cout<<"Movie: "<<node->title<<" ("<<node->rating<<")"<<endl;
    return;
  }else{
    printNodesHelper(node->left, level-1);
    printNodesHelper(node->right, level-1);
  }
}

void MovieTree::printLevelNodes(int level) {
  printNodesHelper(root,level);
}
