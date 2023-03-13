#include <iostream> 
#include <fstream> 
#include <sstream>
#include <string>

using namespace std;

int main(){
    ifstream fin;
    fin.open("output");
    string line;
    while(getline(fin, line)){
        stringstream ss(line);
        getLine()
    }
}