/****************************************************************/
/*                CUBuildingNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CUBuildingNetwork */
/*     This class uses a linked-list of CUBuilding structs to      */
/*     represet communication paths between buildings             */
/****************************************************************/

#include "CUBuildingNetwork.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;
/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CUBuildingNetwork::CUBuildingNetwork() {
    /* finished. do not touch. */
    head = NULL;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CUBuildingNetwork::isEmpty()
{
/* finished. do not touch. */
    return (head == NULL);
}

/*
 * Purpose: Add a new building to the network
 *   between the building *previous and the Building that follows it in the network.
 * @param previous name of the Building that comes before the new Building
 * @param buildingName name of the new Building
 * @param numOfroom
 * @return none
 */

//SEG FAULT GET HELP
void CUBuildingNetwork::addBuildingInfo(CUBuilding* previous, string buildingName, int numOfroom) {
    if(head == NULL){
        CUBuilding *temp = new CUBuilding;
        temp->name=buildingName;
        temp->totalRoom=numOfroom;
        temp->next=NULL;
        head=temp;
        cout<<"adding: "<<buildingName<<" (HEAD) "<<endl;
        previous = head;
    }else{
        if(previous==NULL){
            CUBuilding *temp = new CUBuilding;
            temp->name=buildingName;
            temp->totalRoom=numOfroom;
            temp->next=head;
            cout<<"adding: "<<buildingName<<" (HEAD) "<<endl;
        }else{
            CUBuilding *temp = new CUBuilding;
            temp->name=buildingName;
            temp->totalRoom=numOfroom;
            temp->next=previous->next;
            previous->next=temp;
            cout<<"adding: "<<buildingName<<" (prev: "<<previous->name<<")"<<endl;
        }
    }
    return;
}


/*
 * Purpose: populates the network with the predetermined buildings
 * @param none
 * @return none
 */
void CUBuildingNetwork::loadDefaultSetup()
{
    CUBuilding * prev = new CUBuilding;
    addBuildingInfo(head, "FLMG", 2);
    prev = head;
    addBuildingInfo(prev, "DLC", 10);
    prev = prev->next;
    addBuildingInfo(prev, "ECOT", 6);
    prev = prev->next;
    addBuildingInfo(prev, "CASE", 5);
    prev = prev->next;
    addBuildingInfo(prev, "AERO", 4);
    prev = prev->next;
    addBuildingInfo(prev, "RGNT", 9);
}

/*
 * Purpose: Search the network for the specified building and return a pointer to that node
 * @param buildingName name of the building to look for in network
 * @return pointer to node of buildingName, or NULL if not found
 *
 */
CUBuilding* CUBuildingNetwork::searchForBuilding(string buildingName)
{
    CUBuilding *temp = head;

    while(temp!=NULL){
        if(temp->name==buildingName){
            return temp;
        }else{
            temp = temp->next;
        }
        
    }
    return NULL; 
}


/*
 * Purpose:
 * @param string receiver
 * @param string msg
 */

//Check code runner for progress 
void CUBuildingNetwork::transmitRoomInfo(string receiver) {
    CUBuilding* curr = head;
    if(searchForBuilding(receiver)==NULL){
        cout<<"Building not found"<<endl;
    }else{
        if(curr == 0){
            cout<<"Empty list"<<endl;
        }else{
            while(curr->name != receiver){
                curr->message="available room at "+curr->name+" is " + to_string(curr->totalRoom);
                curr->numberMessages++;
                cout <<  curr->name<<" [# messages received: "<<curr->numberMessages<<"] received: "<<curr->message<<endl;
                curr = curr->next;
            }
            curr->message="available room at "+curr->name+" is " + to_string(curr->totalRoom);
            curr->numberMessages++;
            cout <<  curr->name<<" [# messages received: "<<curr->numberMessages<<"] received: "<<curr->message<<endl;
        }
    }  
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CUBuildingNetwork::printNetwork() {
    CUBuilding * curr = head;
    if(curr=NULL){
        cout<<"nothing in path"<<endl;
    }else{
        cout<<"== CURRENT PATH =="<<endl;
        while(curr !=NULL){
            cout<<curr->name<<"("<<curr->totalRoom<<")"<<" -> ";
            curr=curr->next;
        }
        cout<<"NULL"<<endl;
        cout<<"==="<<endl;
    }

}
