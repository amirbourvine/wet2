//
// Created by amirb on 17/12/2022.
//

#include "Hash_Table_Chain.h"
#include <iostream>


bool isEqual(const int& t1, const int& t2){
    return t1 == t2;
}

bool isEqual_hashobj(const hash_obj<int>& n1, const hash_obj<int>& n2){
    return n1.val==n2.val;
}

int main(){
    Hash_Table_Chain<int> hash(isEqual, isEqual_hashobj);

    for(int i = 0; i<37; i++){
        hash.insert(i*i+5, i+1);
    }
    hash.printHash();

    if(hash.get(38,105).status()==StatusType::SUCCESS){
        cout<<"SUCCESS: " << hash.get(11,105).ans()<<endl;
    }
    else{
        cout<<"FAILURE"<<endl;
    }
}
