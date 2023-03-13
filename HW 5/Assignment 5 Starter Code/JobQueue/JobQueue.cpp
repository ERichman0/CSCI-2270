#include <iostream>
#include "JobQueue.hpp"
using namespace std;

JobQueue::JobQueue(){
    queueFront=0;
    queueEnd=0;
    counter=0;
}

bool JobQueue::isEmpty(){
    if(counter==0){
        return true;
    }else{
        return false;
    }
}

bool JobQueue::isFull(){
    if(counter==SIZE){
        return true;
    }else{
        return false;
    }
}

void JobQueue::enqueue(string job){
    if(isFull()==true){
        cout<<"Queue full, cannot add new job"<<endl;
        return;
    }else{
        if(queueFront==-1){
            queueFront = 0;
            queueEnd = 0;
            queue[queueEnd] = job;
        }else{
            if(queueEnd==SIZE-1){
                queue[0]=job;
                queueEnd=0;
            }else{
                queue[queueEnd]=job;
                queueEnd++;
            }
        }
        counter++;
    }
}
  
void JobQueue::dequeue(){
    if(isEmpty()==true){
        cout<<"Queue empty, cannot dequeue a job"<<endl;
        return;
    }else{
        string result = queue[queueFront];
        if(queueFront == queueEnd){
            queueFront = -1;
            queueEnd = -1;
        }else{
            if(queueFront == SIZE -1){
                queueFront = 0;
            }else{
                queueFront++;
            }
        }
        counter--;
    }
}   

string JobQueue::peek(){
    if(isEmpty()==true){
        cout<<"Queue empty, cannot peek"<<endl;
        return ""; 
    }else{
        return queue[counter];
    }
}

int JobQueue::queueSize(){
    return counter;
}

