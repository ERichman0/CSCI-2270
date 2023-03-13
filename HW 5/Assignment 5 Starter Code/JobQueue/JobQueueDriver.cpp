
#include <iostream>
#include "JobQueue.hpp"

using namespace std;

void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
    cout << "1. Add jobs into the queue" << endl;
	cout << "2. Dispatch jobs from the queue" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}

int main(int argc, char const *argv[])
{
	JobQueue job;
	int choice = 0;
	string temp = "";
	while(choice != 3){
		menu();
		cin>>choice;
		cin.ignore();
		if(choice == 1){
			int numJobs =0;
			string jobName;
			cout<<"Enter the number of jobs to be created: "<<endl;
			getline(cin, temp);
			numJobs = stoi(temp);
			for(int i =0; i<numJobs; i++){
				cout<<"job"<<i+1<<":"<<endl;
				getline(cin, jobName);
				job.enqueue(jobName);
			}
		}else if(choice == 2){
			int numberJobs=0;
			string JOB_NO="";
			JOB_NO="";
			int counter = 0;
			cout<<"Enter the number of jobs to be dispatched:"<<endl;
			getline(cin, JOB_NO);
			numberJobs=stoi(JOB_NO);
			while(job.isEmpty()==false && counter<numberJobs){
				cout<<"Dispatched: "<<job.peek()<<endl;
				job.dequeue();
				counter++;
			}
			if(job.isEmpty()==true){
				cout<<"No more jobs to be dispatched from queue"<<endl;
			}
		}else if(choice==3){
			cout<<"Number of jobs in the queue:"<<job.queueSize()<<endl;
		}
	}
}
