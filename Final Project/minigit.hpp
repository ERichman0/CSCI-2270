#ifndef MG_H
#define MG_H
#include <iostream>
#include <fstream>


using namespace std;

struct singlyNode{
    string filename;
    string fileVersion;
    singlyNode * next;
};

struct doublyNode{
    int commitNumber;
    singlyNode* head;
    doublyNode* prev;
    doublyNode* next;
};

class MiniGit{
    public:
    MiniGit();
    ~MiniGit();
    void init();
    string changeFileName(string fileVersion, string fileName);
    void add(string filename);
    void remove(string filename);
    void commit();
    void checkout(int commitNumber);
    doublyNode* getCommitNode(int x);
    int commitNumber;
    
    private:
    doublyNode* root;
    
};

#endif