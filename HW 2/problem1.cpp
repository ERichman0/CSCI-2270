#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct wordRecord{
    string word;
    int count;
};

void getIgnoreWords(const char *ignoreWordFileName, string ignoreWords[]){
    ifstream fin;
    fin.open(ignoreWordFileName);
    string line;
    if(fin.is_open()){
        string word;
        vector <string> temp;
        while (fin>> word ){
            temp.push_back(word);
        }
        for(int i=0;i<50;i++){
            ignoreWords[i]=temp[i];
        }
    fin.close();
    }else{
        cout<<"Failed to open "<<ignoreWordFileName<<endl;
    }
}

bool isIgnoreWord(string word, string ignoreWords[]){
    for(int i=0; i<50;i++){
        if(word==ignoreWords[i]){
            return true;
        }
    }
    return false;
}

int getTotalNumberNonIgnoreWords(wordRecord distinctWords[], int length){
    int tot=0;
    for(int i=0; i<length; i++){
        tot+=distinctWords[i].count;
    }
    return tot;
}


void sortArray(wordRecord disticntWords[], int length){
    for(int i=0; i<length-1; i++){
        for(int j=0; j<length-i-1; j++){
            if(disticntWords[j].count>disticntWords[j+1].count){
                wordRecord temp=disticntWords[j+1];
                disticntWords[j]=disticntWords[j+1];
                temp=disticntWords[j];
            }
        }
    }
}

void printTenFromN(wordRecord distinctWords[], int N, int totalNumWords){
    for(int i=N; i<N+10; i++){
        float pOO=(float)distinctWords[i].count/totalNumWords;
        cout<<fixed<<setprecision(5)<<pOO<<" - "<<distinctWords[i].word<<endl;
    }
}

void doubleArray(wordRecord *arrPoint, int &cap){
    int newCap = cap*2;
    wordRecord *newArray = new wordRecord[newCap];
    for(int i=0; i<cap; i++){
        newArray[i]=arrPoint[i];
    }
    delete[] arrPoint;

    arrPoint=newArray;
    cap=newCap;
}

int main(int argc, char * argv[]){
    if(argc != 4){
        cout<<"Usage: Assignment2Solution <number of words> <inputfilename.txt> <ignoreWordsfilename.txt>"<<endl;
    }

    int numWords=stoi(argv[1]);
    char *inputFileName= argv[2];
    char *ignoreWordsFile = argv[3];

    ifstream fil(inputFileName);
    
    string ignoreWords[50];
    getIgnoreWords(ignoreWordsFile, ignoreWords);

    if(fil.is_open()){
        int cap=100;
        wordRecord *arrPoint= new wordRecord[cap];

        int size=0;
        int timeDoubled=0;

        string line;
        string word;
        while(getline(fil,line)){
            stringstream ss(line);
            getline(ss,word,' ');
            if(isIgnoreWord(word, ignoreWords)==false){
                wordRecord arrPoint.word=word;
            }
        }
    }else{
        cout<<"Failed to open "<<inputFileName<<endl;
    }
}