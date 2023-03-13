#include <iostream>
#include "StackCalculator.hpp"


using namespace std;
/*
 * Purpose: Determine whether some user input string is a
 *          valid floating point number
 * @param none
 * @return true if the string s is a number
 */
bool isNumber(string s)
{
    if(s.size() == 1 && s == "-")
      return false;

    else if(s.size() > 1 && s[0] == '-')
      s = s.substr(1);

    bool point = false;
    for(int i = 0; i < s.size(); i++){
      if(!isdigit(s[i]) && s[i] != '.')
        return false;
      if(s[i]=='.' and !point) point = true;
      else if(s[i]=='.' and point) return false;
    }

    return true;
}

StackCalculator::StackCalculator()
{
  stackHead = NULL;
}

StackCalculator::~StackCalculator()
{
  Operand *temp=stackHead;
  while(stackHead != NULL){
    temp=stackHead->next;
    delete stackHead;
    stackHead=temp;
  }
}

bool StackCalculator::isEmpty()
{
	if(stackHead == NULL){
    return true;
  }else{
    return false;
  }
}

void StackCalculator::push(float number)
{
  Operand *newNum = new Operand;
  newNum->number=number;
  newNum->next=stackHead;
  stackHead=newNum;
}

void StackCalculator::pop()
{
	if(isEmpty()==true){
    cout<<"Stack empty, cannot pop an item."<<endl;
    return;
  }else{
    Operand *temp = stackHead;
    stackHead=stackHead->next;
    temp->next=NULL;
    delete temp;
    temp=NULL;
  }
}

Operand* StackCalculator::peek()
{
	if(isEmpty()==true){
    cout<<"Stack empty, cannot peek."<<endl;
    return nullptr;
  }else{
    return stackHead;
  }
}

bool StackCalculator:: evaluate(string* s, int size)
{
    int lastIndex=size-1;
    float n;
    for(int i = lastIndex; i>=0; i--){
      if(isNumber(*(s+i))){
        n=stof(*(s+i));
        push(n);
      }else if(*(s+i)=="*" || *(s+i) == "+"){
        float operand1;
        float operand2;
        if(stackHead == NULL || stackHead->next == NULL){
          cout<<"err: not enough operands"<<endl;
          return false;
        }else{
          operand1 = peek()->number;
          operand2 = peek()->next->number;
          if(*(s+i) == "*"){
            pop();
            pop();
            float total1 = operand1 * operand2;
            push(total1);
          }else{
            pop();
            pop();
            float total2 = operand1+operand2;
            push(total2);
          }
        }
      }else{
          cout<<"err: invalid operation"<<endl;
          return false;
      }
    }
    return true;
}
