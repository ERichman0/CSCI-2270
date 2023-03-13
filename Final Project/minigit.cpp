#include <iostream>
#include <fstream>
#include "minigit.hpp"
using namespace std;
#include <filesystem>
namespace fs = std::filesystem;

MiniGit::MiniGit()
{
    commitNumber = 0;
    root = NULL;
    fs::create_directory(".minigit");
}

MiniGit::~MiniGit()
{
    fs::remove_all(".minigit");
    if (root != NULL)
    {
        doublyNode *curr = root;
        doublyNode *prev = NULL;
        while (curr != NULL)
        {
            singlyNode* temp = curr->head;
            singlyNode* prevTemp = NULL;
            while (temp != NULL)
            {
                prevTemp = temp;
                temp = temp->next;
                delete prevTemp;
            }

            prev = curr;
            curr = curr->next;
            delete prev;
        }
    }
}

singlyNode *search(doublyNode *T, string filename)
{
    doublyNode* temp = T;
    if(temp == NULL){
        return NULL;
    }
    singlyNode *curr = temp->head;
    while (curr != NULL)
    {
        if (curr->filename == filename)
        {
            return curr;
        }
        else
            curr = curr->next;
    }
    return NULL;
}

/*Copy files if not equal when commiting*/
void copy(string filename1, string filename2)
{
    ifstream inFile(filename1);
    ofstream outFile(filename2);

    if (!inFile.is_open())
    {
        cout << "No input file found" << endl;
        return;
    }
    if (!outFile.is_open())
    {
        cout << "No output file found" << endl;
        return;
    }

    while (true)
    {
        char c = inFile.get();
        if (c == EOF)
        {
            break;
        }
        outFile << c;
    }

    inFile.close();
    outFile.close();
}

/*Check if files are equal*/
bool equal(string filename1, string filename2)
{
    ifstream file1(filename1), file2(filename2);

    if (!file1.is_open() && !file2.is_open())
    {
        return true;
    }

    if (!file1.is_open() || !file2.is_open())
    {
        return false;
    }

    while (true)
    {
        char c1 = file1.get();
        char c2 = file2.get();
        if (c1 != c2)
        {
            return false;
        }
    }

    return true;
}

doublyNode* MiniGit::getCommitNode(int x)
{
    //allocate memory
    doublyNode *curr = root;
    int count = 0;
    if(curr == NULL){
        return root;
    }
    if (curr->next == NULL)
    {
        return curr;
    }

    while (count != x)
    {
        if (curr->next == NULL)
        {
            return curr;
        }
        curr = curr->next;
        count++;
    }
    return curr;
}



string MiniGit::changeFileName(string fileVersion, string fileName){
    //fileversion:  00_file.txt 
    //filename:  file.txt

    string stringToParse = fileVersion; 
    string delimiter = "_"; 
    string chunk = stringToParse.substr(0, stringToParse.find(delimiter));
    
    int versionNumber = stoi(chunk); //coverting to int removes leading 0s 
    versionNumber = versionNumber + 1 ; 

    if (versionNumber < 10) { //if one digit, add leading 0 
        fileVersion = "0" + to_string(versionNumber) + "_" + fileName; //will this change carry through? 
    }

    else {
        fileVersion = to_string(versionNumber) + "_" + fileName ; 
    }
    return fileVersion;
}

void MiniGit::init(){
    string filename;
    cout<<"Enter the name of the first file you would like to add:"<<endl;
    cin>>filename;
    singlyNode *toBeAdded = new singlyNode;
    toBeAdded->filename=filename;
    toBeAdded->fileVersion= "00_" + filename; //i just changed this, added _ for delimiting purposes 
    copy(filename, ".minigit/" + toBeAdded->fileVersion);//putting contents of file into "new" file version file in minigit 
    doublyNode *d= new doublyNode;
    d->commitNumber=0;
    d->head=toBeAdded;
    d->next=nullptr;
    d->prev=nullptr;
    root=d;
}

void MiniGit::add(string filename){
   ofstream f;
   f.open(filename);
   if(!f.is_open()){
       cout<<"The file you inputed does not exist."<<endl;
       return;
   }else{
       f.close();
       if(search(getCommitNode(commitNumber),filename) != NULL){
           cout<<"A file with this name has already been added"<<endl;
           return; //isn't the point that i need to change the file name because it is the same ? so wil it 
           //even reach the else portion 
        }
        else{
           //Adding to linked list
           singlyNode *toBeAdded = new singlyNode;
           toBeAdded->filename=filename;

           if(search(getCommitNode(commitNumber-1),toBeAdded->filename) != NULL){
                toBeAdded->fileVersion = changeFileName(search(getCommitNode(commitNumber -1), toBeAdded->filename)->fileVersion, toBeAdded->filename);
           }

           else {
               toBeAdded->fileVersion = "00_" + filename; //first file 
           }

           
           singlyNode *temp= getCommitNode(commitNumber)->head;
           while(temp->next!=NULL){
               temp=temp->next;
           }
           temp->next=toBeAdded;
           
           toBeAdded->next=NULL;
          //copy contents into new file 
          copy(toBeAdded->filename, ".minigit/" + toBeAdded->fileVersion);//putting contents of file into "new" file version file in minigit 

       }
   }
}


void MiniGit::remove(string filename)
{
    singlyNode *toBeRm = search(getCommitNode(commitNumber), filename);
    singlyNode *curr = getCommitNode(commitNumber)->head; //need to set to head of DLL
    singlyNode *prev = NULL;
    while (curr != NULL)
    {
        if (curr == toBeRm)
        {
            break;
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
    if (curr == NULL)
    {
        cout << "File does not exist" << endl;
        return;
    }
    else
    {
        if (prev == NULL)
        { //first node is to be deleted
            getCommitNode(commitNumber)->head = curr->next; //need to set to head of DLL
            fs::remove(".minigit/" + curr->fileVersion);
            curr = NULL;
            return;
        }
        else
        {
            prev->next = curr->next;
            fs::remove(".minigit/" + curr->fileVersion);
            delete curr;
        }
    }
}

void MiniGit::commit(){
//traverse through current commit and check if file(s) are in minigit directory 

singlyNode * crawler = getCommitNode(commitNumber)->head;
commitNumber ++; 

doublyNode* DLLNode = new doublyNode; //preparing new DLL node 
DLLNode->commitNumber = commitNumber; 

    while(crawler != NULL){ //for every file in previous commit's SLL
        
        
        string currFile = "text.txt";  //== crawler.filename 
        string check = ".minigit/" + crawler->fileVersion; 
        fstream file; 
        file.open(check);
        if(file.is_open()) {
            if (!equal(currFile, check)) { 
                add(currFile);  //only adding currfile if the user has made changes and hasn't added it yet 
                cout << "**" << endl;
            }

            else { 
                singlyNode* newCrawler = DLLNode->head; //new crawler going through all the SLL of our new commit that we're creating 
                while (newCrawler->next != NULL){
                    newCrawler = newCrawler->next; 
                }
                //now we're at the end of SLL 
                newCrawler->fileVersion = crawler->filename;  
                newCrawler->filename = currFile; 
            }

        }

    file.close();
    crawler = crawler->next; //move on 
    }
    return;

}
void MiniGit::checkout(int commitNumber){
    doublyNode *checkout = getCommitNode(commitNumber);
    singlyNode *curr = checkout->head;
    while(curr != NULL){
        ifstream inFile(".minigit/" + curr->fileVersion);
        ofstream outFile(curr->filename);

        while (true)
        {
            char c = inFile.get();
            if (c == EOF)
            {
                break;
            }
            outFile << c;
        }
        
        inFile.close();
        outFile.close();
        curr = curr->next;
    }
}
