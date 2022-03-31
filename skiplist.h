/*
* This file contains the protoypes for the SkipList class
*/
#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <iostream> 

using namespace std; 

class SkipList{


    public:
        explicit SkipList(int depth);
        virtual ~SkipList();
        bool Add(int data);
        bool Remove(int data);
        bool Contains(int data);
        friend ostream &operator<<(ostream &os, const SkipList &list);
    
    private: 
        class SNode{ // private class for SNode
            public: 
                explicit SNode(int data);
                SNode *next; //pointers to other levels and around 
                SNode *prev;
                SNode *upLevel;
                SNode *downLevel;
                int data;
        };

    int depth;
    SNode **frontGuards; //pointers for guards
    SNode **rearGuards;

    void addBefore(SNode *newNode, SNode *nextNode); 
    bool alsoHigher() const; 

};



#endif 
