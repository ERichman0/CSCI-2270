#include <iostream>
#include <string>
using namespace std;

// any file that uses the SLL class must include this header file
#include "SLL.hpp"

int main(){
   
	/*
	Test cases are provided only to help you test your code. Each
	submission will be individually inspected by the teaching staff.

	*/

    /*
    Test 1
    */
    cout << "\n---------------------\n";
	int n = 5;
	char testStringA[] = {'m','a','d','a','m'};
	SLL sA;
	for(int i = 0; i<n; i++){
		sA.insert(nullptr,testStringA[i]);
	}
	cout << "Test A:" << endl; 
	sA.displayList();

	cout << "expected >> Palindrome " << endl;

	if(sA.palindrome())
		cout << "result   >> Palindrome" << endl;
	else
		cout << "result   >> Not a palindrome" << endl;
	    cout << "\n---------------------\n";

	/*
    Test 2
    */
    cout << "\n---------------------\n";
	char testStringB[] = {'m','a','d','m','a'};
	SLL sB;
	for(int i = 0; i<n; i++){
		sB.insert(nullptr,testStringB[i]);
	}
	cout << "Test B: \n";
	sB.displayList();
	cout << "expected >> Not a palindrome " << endl;
	if(sB.palindrome())
		cout << "result   >> Palindrome" << endl;
	else
		cout << "result   >> Not a palindrome" << endl;
    cout << "\n---------------------\n";


	return 0;
}
