/* 
* This file contains the implementations for the SkipList class
*/
#include <iostream> 
#include <cassert>
#include <climits>
#include "skiplist.h"

using namespace std; 

SkipList::SkipList(int depth){
    if(depth < 1 ){ //throw error in case invalid depth
        throw invalid_argument("Depth must be 1 or greater");
    }

    this->depth = depth;
    this->rearGuards = new SNode* [depth]; //make space for a new skiplist
    this->frontGuards = new SNode* [depth];
    for(int i = 0; i<depth; i++){
        this->frontGuards[i] = new SNode (INT_MIN); //initialize the new skiplist
        this->rearGuards[i] = new SNode (INT_MAX);
        this->frontGuards[i]->next = this->rearGuards[i];
        this->rearGuards[i]->prev = this->frontGuards[i];
        
        if(i > 0){
            this->frontGuards[i]-> downLevel = this->frontGuards[i-1]; //go to the other levels
            this->frontGuards[i-1]->upLevel = this->frontGuards[i];
            this->rearGuards[i]-> downLevel = this->rearGuards[i-1];
            this->rearGuards[i-1]->upLevel = this->rearGuards[i];
            
        }
    }

    this->frontGuards[0]->downLevel = nullptr; // create links to other levels 
    this->frontGuards[depth-1]->upLevel = nullptr;
    this->rearGuards[0]->downLevel = nullptr;
    this->rearGuards[depth-1]->upLevel = nullptr;
}

SkipList::~SkipList(){
    SNode *end, *node; // delete every single node with a for loop 
    for(int i = depth-1; i>=0; i--){ 
        node=frontGuards[i];
        while(node != nullptr){
            end=node;
            node=node->next;
            delete end;

        }
        delete node;
    }

    delete []rearGuards;
    delete []frontGuards; //delete both guards
}


bool SkipList::Add(int data) {
    SNode *nxNode=frontGuards[0]->next;
    while(nxNode->next!= nullptr && nxNode->data < data) {
        nxNode=nxNode->next;
    }
    if(nxNode->data == data) { // if it is a duplicate copy return false 
        return false;
    }
    SNode *newNode=new SNode(data);
    addBefore(newNode, nxNode);
    int count=1;
    while(count<depth){
        if(alsoHigher()){
            SNode *nUpper=new SNode(data);
            nUpper->downLevel=newNode; //create links to other levels
            newNode->upLevel=nUpper;
            SNode *node=newNode->prev;
            while(node->upLevel == nullptr) { //as long a null move on to other node
                node=node->prev;
            }
            count++;
            node=node->upLevel;
            node=node->next;
            addBefore(nUpper, node);
            newNode=nUpper;
        }else
            break;
    }
    return true;
}



SkipList::SNode::SNode(int data){
    this->data = data;
    this->next = nullptr;
    this->prev = nullptr; //link to the previous snode
    this->upLevel = nullptr; //link above a level
    this->downLevel = nullptr; //link down one level
}

bool SkipList::Remove(int data) {
  SNode *pres = nullptr;
  SNode *end = nullptr;
  for (int i = depth - 1; i >= 0; i--) { //start from the top 
    pres = frontGuards[i]->next;
    while (pres->next != nullptr && pres != frontGuards[i]) {
      if (pres->data == data) { //if the data is found 
        while (pres != nullptr) {
          pres->prev->next = pres->next; // go to next node
          pres->next->prev = pres->prev;
          end = pres;
          pres = pres->downLevel; //go down a level
          delete end;
          end = nullptr;
        }
        return true;
      }
      pres = pres->next;
    }
  }
  return false;
}

void SkipList::addBefore(SNode *newNode, SNode *nextNode){
    assert(newNode != nullptr && nextNode != nullptr && newNode->data < nextNode->data); //assert to check condtions
    SNode *lastNode = nextNode->prev;   
    lastNode->next=newNode;
    newNode->prev=lastNode;
    newNode->next=nextNode;
    nextNode->prev=newNode;
    assert(newNode->next == nextNode && nextNode->prev == newNode);
    assert(newNode->prev != nullptr && newNode->prev->data < newNode->data);
} 

bool SkipList::Contains(int data){
    SNode *pres = frontGuards[depth-1]; //search from the highest level
    while(pres!=nullptr){
        while(pres->next->data<data){ //keep moving in the same direction 
            pres=pres->next;
        }
        if(pres->next->data==data){ //once the data is found 
            return true;
        }
        pres=pres->downLevel; // go down one level
    }
    return false;
}

bool SkipList::alsoHigher() const{ 
    return rand() % 2 == 1;  // create a 50 percent chance to be added to a different level
}

ostream &operator<<(ostream &out, const SkipList &sl){
    for(int i = sl.depth-1; i>=0; i--){ //print each level of list
        SkipList::SNode *node = sl.frontGuards[i];
        out<<"List Level "<<i<<": ";
        while(node != nullptr){ //as long as node isnt null
            out<<node->data<<", ";
            node = node->next; //move to next
        }
        out<< endl;
    }
    return out;
}


