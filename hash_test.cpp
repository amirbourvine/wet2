//
// Created by amirb on 17/12/2022.
//

#include "Hash_Table.h"
#include <iostream>


bool isEqual(const int& t1, const int& t2){
    return t1 == t2;
}

int main(){
    Hash_Table<int> hash(isEqual);
    hash.insert(15, 5);
    hash.printHash();
    hash.insert(14, 3);
    hash.printHash();
    hash.insert(7, 1);
    hash.printHash();
    hash.insert(-3, 9);
    hash.printHash();
    hash.insert(2, -4);
    hash.printHash();
    hash.insert(5, -7);
    hash.printHash();
    hash.insert(6, -1);
    hash.printHash();
    if(hash.get(-4,19).status()==StatusType::SUCCESS){
        cout<<"SUCCESS: " << hash.get(-4,19).ans()<<endl;
    }
    else{
        cout<<"FAILURE"<<endl;
    }
}
