/* 
* This file contains the tests for the SkipList class
*/
#include "skiplist.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>

using namespace std; 

void test01() {
    cout<<"Testing add() function: "<< endl;
    SkipList sl1(5); //construct 5 levels 
    sl1.Add(9);
    sl1.Add(10); 
    sl1.Add(22); 
    sl1.Add(44);
    sl1.Add(5);
    sl1.Add(3);
    sl1.Add(4);
    sl1.Add(55); //add all elements
    cout << sl1 << endl; 
    cout << "Test 1 complete" << endl;
    cout << endl;

}

void test02() {
    cout<<"Testing the Contains() method: " <<endl;
    SkipList sl2(5); //construct 5 levels 
    sl2.Add(33);
    sl2.Add(10);
    sl2.Add(11);
    sl2.Add(99);
    sl2.Add(6);
    sl2.Add(27);
    sl2.Add(12);
    sl2.Add(44);
    sl2.Add(89);

    cout << sl2 << endl;
    if (sl2.Contains(44)) {
        cout << "SkipList DOES contain 44:" << endl; 
    } else {
        cout << "SkipList DOES NOT contain 44:" << endl;
    }

    if (sl2.Contains(35)) {
        cout << "SkipList DOES contain 35:" << endl; 
    } else {
        cout << "SkipList DOES NOT contain 35:" << endl;
    } 
    cout << "Test 2 is successful" << endl;
    cout << endl;

}

void test03() {
    cout<<"Test the Remove() and Contains() "<<endl;
    SkipList sl3(3); //construct 3 levels 
    sl3.Add(37);
    sl3.Add(16);
    sl3.Add(12);
    sl3.Add(85);
    sl3.Add(63);
    sl3.Add(27);
    sl3.Add(14);
    sl3.Add(49);
    sl3.Add(89);
    cout << sl3 << endl;

    if (sl3.Contains(14)) {
        cout << "SkipList DOES contain 11:" << endl;
    }
    else {
        cout << "SkipList DOES NOT contain 11:" << endl;
    }

    sl3.Remove(14);
    cout << "14 has been removed: "<<endl;
    if (sl3.Contains(14)) {
        cout << "SkipList DOES contain 14:" << endl;
    }
    else {
        cout << "SkipList DOES NOT contain 14:" << endl;
    }
    cout << sl3 << endl;


    cout << "Test 3 is successful" << endl;

}

void test04(){
    cout << "Testing invalid constructor" << endl;
    try{
        SkipList sl4(0); //create invalid constructor
    } catch (const exception &e){
        cerr<<e.what()<<endl;
    }
    cout << "Test 4 is successful"<<endl;
}

void test05() {
    SkipList sl4(60); //construct 4 levels 

    for (int i = 0; i < 100000; ++i) { //create multiple random elements to test add 
        int num = rand() % 1000000;
        sl4.Add(num);

        //cout << "After adding " << num << endl;
    }
    cout << sl4 << endl;
    cout << "Test 5 is successful"<<endl;
}


int main(){
    
    //cout << "Running Test 1" << endl;
    //test01();
    //cout<<" "<< endl; //formatting spaces

    //cout << "Running Test 2" << endl;
    //test02();
    //cout<<" "<< endl; 

    //cout << "Running Test 3" << endl;
    //test03(); 
    //cout<<" "<< endl;

    //cout << "Running Test 4" << endl;
    //test04();
    //cout<<" "<< endl;

    cout << "Running Test 5" << endl;
    test05();
    cout<<" "<< endl;
}

