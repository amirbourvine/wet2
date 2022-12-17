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
}
