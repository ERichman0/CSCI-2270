#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>

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

void swap(float *xp, float *yp){
    float temp= *xp;
    *xp= *yp;
    *yp= temp;
}

void sortArray(wordRecord distinctWords[], int length){
    for(int i=0; i<length-1; i++){
        for(int j=0; j<length-i-1; j++){
            if(distinctWords[j].count<distinctWords[j+1].count){
                swap(distinctWords[j],distinctWords[j+1]);
            }
        }
    }
}

void printTenFromN(wordRecord distinctWords[], int N, int totalNumWords){
    wordRecord hold;
    for(int i=N; i<N+10; i++){
        for(int j=N; j<N+10; j++){
            if(distinctWords[i].count== distinctWords[j].count){
                if(distinctWords[i].word<distinctWords[j].word){
                    hold=distinctWords[i];
                    distinctWords[i]=distinctWords[j];
                    distinctWords[j]=hold;
                }
            }
        }
    }
    for(int i=N; i<N+10; i++){
        float pOO=(float)distinctWords[i].count/totalNumWords;
        cout<<fixed<<setprecision(5)<<pOO<<" - "<<distinctWords[i].word<<endl;
    }
}

int distinctWord(const string &word, wordRecord *items, int size){
    for (int i = 0; i < size; i++){
        if (word == items[i].word)
            return i; 
    }
    return -1; 
}

wordRecord* doubleArray(wordRecord *arrayPtr, int &cap){
    int newCap = cap * 2;
    wordRecord *newArray = new wordRecord[newCap];

    for (int i = 0; i < cap; i++){
        newArray[i] = arrayPtr[i];
    }
    delete[] arrayPtr;
    arrayPtr=0;

    cap = newCap;
    return newArray;
}

int main(int argc, char *argv[]){
    if (argc != 4){
        cout << "Usage: Assignment2Solution <number of words> <inputfilename.txt> <ignoreWordsfilename.txt> " << endl;
    }

    int numWords = stoi(argv[1]);

    char *inputFileName = argv[2];
    ifstream wordsFile(inputFileName);

    char *ignoreWordsFileName = argv[3];
    string ignoreWords[50];
    getIgnoreWords(ignoreWordsFileName, ignoreWords);

    int cap=100;

    wordRecord *words = new wordRecord[cap];

    if (!wordsFile.is_open()){
        cout << "Failed to open " << inputFileName<< endl;
        return -1;
    }

    int size = 0;             
    int timesDoubled = 0; 
    string line;          
    string word;

    while (wordsFile>>word){
        //cout<<"First getLine works"<<endl;
        // while(getline(linestream, word, ' ')){
        //     cout<<word<<endl;
        //     //cout<<"Second getLine works"<<endl;
        //     if(word.empty()){
        //         continue;
        //     }
        //cout<<word<<endl;
            if (isIgnoreWord(word, ignoreWords)==false){
                //cout<<"Ignore word worked"<<endl;
                int wordIndex = distinctWord(word, words, size);
                //cout<<"Distinct word worked"<<endl;
                if (wordIndex == -1){//Infinite loop of wordIndex
                    //cout<<"wordIndex = -1 worked"<<endl;
                    wordRecord wordItem;
                    wordItem.count = 1;
                    wordItem.word = word;
                    words[size] = wordItem; 
                    //cout<<"Before sortArray"<<endl;
                    size++;
                    //cout<<"sortArray worked"<<endl;
                    if (size == cap){
                        //cout<<"starting array doubling worked"<<endl;
                        words=doubleArray(words, cap);
                        // int newCap = cap * 2;
                        // wordRecord *newArray = new wordRecord[newCap];
                        // for (int i = 0; i < cap; i++){
                        //     newArray[i] = words[i];
                        // }
                        // delete[] words;
                        // words=0;
                        // words = newArray;
                        // cap = newCap;    
                        timesDoubled++;
                        //cout<<"Ending array doubling worked"<<endl;
                        //cout<<timesDoubled<<endl;
                    }
                }else{
                    words[wordIndex].count++;
                }
            }
        }
    sortArray(words, size);
    wordsFile.close();
    cout<<"Array doubled: "<<timesDoubled<<endl;
    cout<<"Distinct non-common words: "<<size<<endl;
    cout<<"Total non-common words: "<<getTotalNumberNonIgnoreWords(words, size)<<endl;
    cout<<"Probability of next 10 words from rank "<<numWords<<endl;
    cout<<"---------------------------------------"<<endl;
    printTenFromN(words, numWords, getTotalNumberNonIgnoreWords(words, size));

    return 0;
}