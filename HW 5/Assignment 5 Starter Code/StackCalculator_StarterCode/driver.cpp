#include<iostream>
#include<cmath>
#include<iomanip>
#include "StackCalculator.hpp"

using namespace std;



int main()
{
  // stack to hold the operands
  StackCalculator stack;

  int numElement = 0;
  string* inparr = new string[50];

  // enter a number
  string number;
  cout << "Enter the operators and operands ('+', '*') in a prefix format" << endl;

  while(true)
  {
    cout << "#> ";
    getline(cin, number);
   if(number != "="){
     inparr[numElement]=number;
     numElement++;
   }
   if(number == "="){
     break;
   }
   

  }

  bool b = false;
  if(numElement==0){
    cout<<"No operands: Nothing to evaluate"<<endl;
    return 0 ;
  }else{
    b = stack.evaluate(inparr, numElement);
  }

  if(b = true){
    if(stack.isEmpty()==true){
      return 0;
    }
    float result = stack.peek()->number;
    stack.pop();
    if(stack.isEmpty()){
      cout<<"Result= "<<result<<endl;
    }
  }

  delete[] inparr;
 
  return 0;
}
