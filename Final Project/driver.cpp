#include <iostream>
#include <fstream>
#include "minigit.hpp"

using namespace std;

void displayMenu(){
    cout << "Select an option:" << endl;
    cout << "+====MAIN MENU====+" << endl;
    cout << "1. Add" << endl;
    cout << "2. Remove" << endl;
    cout << "3. Commit" << endl;
    cout << "4. Checkout" << endl;
    cout << "5. Quit" << endl;
    cout << "+=================+" << endl;
}

int main(){
    MiniGit MG;

    int choice=0;
    cout<<"Would you like to initialize a respository?"<<endl;
    cout<<"1. Yes"<<endl;
    cout<<"2. No"<<endl;
    cin>>choice;
    bool open=true;
    if(choice==1){
        MG.init();
    }else{
        cout<<"You have to initalize a repository to begin"<<endl;
        return 0;
    }
    if(open==true){
        while(true){
        displayMenu();
        cout << "*> ";
        int x, choice;
        cin >> x;
        switch(x){
            case 1:
            {
                string filename;
                cout << "Enter filename: ";
                cin >> filename;
                cout << endl;
                MG.add(filename);
                break;
            }
            case 2:{
                string filename;
                cout << "Enter filename to be deleted: ";
                cin >> filename;
                cout << endl;
                MG.remove(filename);
                break;
            }
            case 3:
            {
                cout << "Commiting..." << endl;
                MG.commit();
                cout << "New commit saved with commit number: " << MG.commitNumber - 1 << endl;;
                break;
            }
            case 4:{
                int num;
                cout << "Enter commit number to be checked out: ";
                cin >> num;
                cout << endl;
                MG.checkout(num);
                break;
            }
            case 5: choice = 5; break;
            default: cout << "*> ";
        }
        if(choice == 5){
            break;
        }
    }
    }else{
        return 0;
    }
    
}