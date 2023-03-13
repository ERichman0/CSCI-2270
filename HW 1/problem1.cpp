#include <iostream>
#include <fstream>
using namespace std;

void swap(float *xp, float *yp){
    float temp= *xp;
    *xp= *yp;
    *yp= temp;
}

void bubbleSort(float arr[], int n){
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(arr[j]>arr[j+1]){
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

int addToArrayAsc(float sortedArray[], int numElements, float newValue){
    sortedArray[numElements-1]=newValue;
    //bubbleSort(sortedArray, numElements);
    for(int i=0; i<(numElements-1); i++){
        for(int j=0; j<(numElements-i-1); j++){
            if(sortedArray[j]>sortedArray[j+1]){
                swap(&sortedArray[j], &sortedArray[j+1]);
            }
        }
    }
    for(int i=0; i< numElements; i++){
        if(i==0){
            cout<<sortedArray[i];
        }else{
            cout<<","<<sortedArray[i];
        }
    }
    cout<<endl;
    return numElements;
}

int main(int argc, char* argv[]){
    float arr[100];
    int numElements=0;
    
        ifstream fin;
        string filename=argv[1];
        fin.open(filename);

        if(fin.is_open()){
            string line;
            while(getline(fin,line)){
                float val=stof(line);
                arr[numElements]=val;
                numElements++;
                addToArrayAsc(arr,numElements,val);
            }
        }else{
            cout<<"Failed to open the file."<<endl;
        }
}
