#include <iostream>

using namespace std;

bool append(string * &str_arry, string s, int &numEntries, int &arraySize){
    bool b=false;
    if(numEntries<arraySize){
        str_arry[numEntries]=s;
        numEntries++;
    }else{
        int newCap = arraySize*2;
        string *newArray = new string[newCap];

        for (int i = 0; i < arraySize; i++){
            newArray[i] = str_arry[i];
        }

        delete[] str_arry;
        str_arry=0;

        arraySize = newCap;
        str_arry=newArray;

        str_arry[numEntries]=s;

        numEntries++;
        b=true;
    }
    return b;
}