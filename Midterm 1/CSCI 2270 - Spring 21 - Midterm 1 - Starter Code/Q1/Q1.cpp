/*
CSCI 2270 - Spring 2021
Midterm 1
Question 1 starter code.

*/


#include <iostream>
#include <vector>

using namespace std;

void trim(int arr[], int length, int target);

void testPrint(int *p0, int length);

int main(){
   
    int a_test[] = {3, 2, 5 ,1, 0, 8, 4};
    int test_length = 7;
   
   
    /*
    Test 1
    */
    cout << "\n---------------------\n";
    
    int * a0 = new int[test_length];
    for(int i = 0; i<test_length; i++){
        a0[i] = a_test[i];
    }

    int target = 0; 
    

    trim(a0, test_length, target);

    cout << "Test 1: \n"  << "expected >> 3 2 5 1 " << endl;
    testPrint(a0, test_length);
    delete [] a0;

    return 0;
}



//Comeback to if time allows to figure out how to remove the 0's
void trim(int *arr, int length, int target){
    for(int i=0; i<length; i++){//iterate through array to find target value
        if(arr[i]==target){//check to see if value of array is the target value 
            for(int j=i; j<length; j++){//iterate through again from the target value
                arr[j]=arr[j+length];//move the values that come after the tagert value out of the array
            }
            length=i;// alter the length
        }
    }
}



void testPrint(int *p0, int length){
    
    cout << "result   >> ";

    for(int i = 0; i<length; i++){
        if(p0[i]!=0){
            cout << p0[i] << " ";
        }
    }
    cout << "\n---------------------\n\n" << endl;
}