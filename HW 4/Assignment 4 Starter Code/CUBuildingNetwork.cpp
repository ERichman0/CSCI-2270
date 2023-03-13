/*******************************************************************/
/*                CUBuildingNetwork Implementation                 */
/*******************************************************************/
/* TODO: Implement the member functions of class CUBuildingNetwork */
/*       This class uses a linked-list of CUBuilding nodes to      */
/*       represent communication paths between buildings           */
/*******************************************************************/

#include "CUBuildingNetwork.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

/*
 * Purpose: Constructor for empty linked list
 * @param none
 * @return none
 */
CUBuildingNetwork::CUBuildingNetwork() 
{
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
 *   between the CUBuilding *previous and the CUBuilding that follows it in the network.
 * @param previous name of the Building that comes before the new Building
 * @param buildingName name of the new Building
 * @param numOfroom
 * @return none
 */
void CUBuildingNetwork::addBuildingInfo(CUBuilding* previous, string buildingName, int totalRoom) 
{
    if(head == NULL){
        CUBuilding *temp = new CUBuilding;
        temp->name=buildingName;
        temp->totalRoom=totalRoom;
        temp->next=NULL;
        head=temp;
        cout<<"adding: "<<buildingName<<" (HEAD) "<<endl;
        previous = head;
    }else{
        if(previous==NULL){
            CUBuilding *temp = new CUBuilding;
            temp->name=buildingName;
            temp->totalRoom=totalRoom;
            temp->next=head;
            cout<<"adding: "<<buildingName<<" (HEAD) "<<endl;
        }else{
            CUBuilding *temp = new CUBuilding;
            temp->name=buildingName;
            temp->totalRoom=totalRoom;
            temp->next=previous->next;
            previous->next=temp;
            cout<<"adding: "<<buildingName<<" (prev: "<<previous->name<<")"<<endl;
        }
    }
    return;

}

/*
 * Purpose: populates the network with the predetermined CUBuildings
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
    // MODIFICATION: Use deleteEntireNetwork function before adding buildings

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
 * Purpose: Relay a message through the linked list until the specified CUBuilding
 * @param string receiver
 * @param string msg
 */
void CUBuildingNetwork::transmitRoomInfo(string receiver)
{
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
void CUBuildingNetwork::printNetwork() 
{
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

/****************************************************/
/*  ASSIGNMENT 4: Functions to be completed below.  */
/****************************************************/

/*
 * Purpose: Delete the CUBuilding in the network with the specified name.
 * @param buildingName name of the CUBuilding to delete in the network
 * @return none
 */
void CUBuildingNetwork::deleteCUBuilding(string buildingName) 
{
    if(searchForBuilding(buildingName)==NULL){
        cout<<"Building does not exist."<<endl;
        return;
    }else{
        CUBuilding *curr = head;
        CUBuilding *prev = NULL;
        while(curr != NULL){
            string name =curr->name;
            if(name==buildingName){
                break;
            }else{
                prev=curr;
                curr=curr->next;
            }
        }

        if(prev==0){
            head=curr->next;
            delete curr;
        }else{
            prev->next=curr->next;
            delete curr;
        }
    }

}

/*
 * Purpose: deletes all CUBuildings in the network starting at the head CUBuilding.
 * @param: none
 * @return: none
 */
void CUBuildingNetwork::deleteEntireNetwork()
{
    CUBuilding *curr = head;
    CUBuilding *temp;
    CUBuilding *prev = NULL;
    if(curr==NULL){
        return;
    }else{
        while(curr != NULL){
            cout<<"deleting: "<<curr->name<<endl;
            temp=curr->next;
            prev=curr;
            delete prev;
            curr=temp;
        }
        cout<<"Deleted network"<<endl;
        head=NULL;
    }
}

/*
* Purpose: Creates a loop from last node to the CUBuilding specified.
* @param buildingName name of the CUBuilding to loop back
* returns the last node before loop creation (to break the loop)
*/
CUBuilding* CUBuildingNetwork::createLoop(string buildingName) 
{
    //find last node
    CUBuilding *tail = head;
    while(tail->next != NULL){
        tail=tail->next;
    }

    //find linked node and create loop
    if(searchForBuilding(buildingName)==NULL){
        return tail;
    }else{
        CUBuilding *linked = searchForBuilding(buildingName);
        tail->next=linked;
        return tail;
    }
}

/*
 * Purpose: to detect loop in the linked list
 * @return: true if loop is detected, else false
 */
bool CUBuildingNetwork::detectLoop() 
{
    if(head==NULL){
        return false;
    }else{
        CUBuilding *curr = head->next;
        CUBuilding *prev = head;

        while(curr != NULL && prev != NULL && curr->next != NULL){
            if(curr == prev){
                return true;
            }
            curr=curr->next->next;
            prev=prev->next;
        }
        return false;
    }
}

/*
 * Purpose: Take the chunk of nodes from start index to end index
 *          Move that chunk to the end of the List
 * @param: start_index, end_index
 * @return: none
 */
void CUBuildingNetwork::readjustNetwork(int start_index, int end_index)
{
    CUBuilding *end = head;
    CUBuilding *prev;
    CUBuilding *endOfList = head;
    CUBuilding *startOfSection = head;

    int totalIndex = 0;
    if(head == NULL){
        cout<<"Linked List is Empty"<<endl;
        return;
    }
    while(endOfList->next != NULL){
        endOfList = endOfList->next;
        totalIndex++;
    }
    if(end_index >= totalIndex){
        cout<<"Invalid end index"<<endl;
        return;
    }
    if(start_index >= totalIndex || start_index<0){
        cout<<"Invalid start index"<<endl;
        return;
    }
    if(start_index>end_index){
        cout<<"Invalid indices"<<endl;
        return;
    }
    if(start_index==0){
        for(int i=0; i<end_index; i++){
            end = end->next;
        }
        head = end->next;
        endOfList->next=startOfSection;
        end->next = NULL;
    }else{
        for(int i=0; i<start_index; i++){
            if(i == start_index-1){
                prev = startOfSection;
            }
            startOfSection=startOfSection->next;
        }
        end = startOfSection;
        for(int h = 0; h<(end_index-start_index); h++){
            end = end->next;
            return;
        }
        if(start_index == 0){
            for(int i=0; i<end_index; i++){
                end = end->next;
            }
            head = end->next;
            endOfList->next=startOfSection;
            end->next = NULL;
        }else{
            for(int i=0; i<start_index; i++){
                if(i == start_index-1){
                    prev=startOfSection;
                }
                startOfSection = startOfSection->next;
            }
            end=startOfSection;
            for(int h=0; h<(end_index-start_index); h++){
                end = end->next;
            }
            prev->next = end->next;
            endOfList->next = startOfSection;
            end->next = NULL;
        }
    }
    return;

}

/*
 * Purpose: Destructor to delete the entire list on program termination
 * @param none
 * @return none
 */
CUBuildingNetwork::~CUBuildingNetwork()
{
    // TODO: Complete this function

}
