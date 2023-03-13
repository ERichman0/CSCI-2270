#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>

using namespace std;

struct studentData{
    string studentName;     
    int homework;     
    int recitation;    
    int quiz;     
    int exam;    
    double average; 
};

char calcLetter(double avg){
    if(avg>=90.0){
        return 'A';
    }else if(avg<=89.9&&avg>=80.0){
        return 'B';
    }else if(avg<=79.9&&avg>=70.0){
        return 'C';
    }else if(avg<=69.9&&avg>=60.0){
        return 'D';
    }else if(avg<60){
        return 'F';
    }else{
        return 'I';
    }
}

void printList(const studentData students[], int length){
    for (int i=0; i<length; i++){
        cout<<students[i].studentName<<" earned "<< students[i].average<< " which is a(n) "<<calcLetter(students[i].average)<<endl;
    }
}

void addStudentData(studentData students[], string studentName, int homework, int recitation, int quiz, int exam, int length){
    studentData student;
    student.studentName=studentName;
    student.homework=homework;
    student.recitation=recitation;
    student.quiz=quiz;
    student.exam=exam;

    student.average=(homework+recitation+quiz+exam)/4.0;
    students[length]=student;
    //printList(students, length);
}

int main(int argc, char* argv[]){
    if(argc >= 5){
        char low = argv[3][0];
        char high = argv[4][0];
        studentData students[10];
        char *outputname=argv[2];
        string line;
        string studentName;
        string tempHW;
        string tempRec;
        string tempQ;
        string tempExam;
        int length = 0;
        int HW;
        int Rec;
        int Q;
        int Exam;
        char grade;
        ifstream filename;
        filename.open(argv[1]);
        if(filename.is_open()){
            while(getline(filename, line)){
                stringstream read(line);
                getline(read, studentName, ',');
                getline(read, tempHW, ',');
                HW = stoi(tempHW);
                getline(read,tempRec,',');
                Rec = stoi(tempRec);
                getline(read, tempQ, ',');
                Q = stoi(tempQ);
                getline(read, tempExam, ',');
                Exam = stoi(tempExam);
                addStudentData(students, studentName, HW, Rec, Q, Exam, length);
                length++;
            }
            printList(students, length);
            filename.close();
        }else{
            cout<<"File could not open."<<endl;
        }
        ofstream myFile;
        myFile.open(outputname);
        if(!myFile){
            cout<<"something went wrong"<<endl;
        }else{
            for(int i=0; i<length; i++){
                char grade = calcLetter(students[i].average);
                if(grade >= int(high) && grade <= int(low)){
                    myFile<<students[i].studentName<<","<<students[i].average<<","<<grade<<endl;
                }
            }
            myFile.close(); 
        }
    }else{
        cout<<"Not enough content"<<endl;
    }
}