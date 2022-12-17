//
// Created by amirb on 17/12/2022.
//

#include "Hash_Table.h"

bool isEmpty(const int& val){
    return val == NULL;
}

bool isEqual(const int& t1, const int& t2){
    return t1 == t2;
}

int main(){
    Hash_Table<int> hash(isEmpty, isEqual);
}
