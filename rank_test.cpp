//
// Created by amirb on 20/12/2022.
//
#include "RankTree.h"

bool isLarger(const int& x, const int& y){
    return x>y;
}

bool isEqual(const int& x, const int& y){
    return x==y;
}

int main(){
    RankTree<int>* root = new RankTree<int>(isLarger, isEqual);
    root->insert(1);
    root->print2D();
    cout<<"********************************************************************"<<endl;

//    StatusType st = root->remove(20);
//    if(st!=StatusType::SUCCESS){
//        cout<<"SUCCESS"<<endl;
//    }
//    else{
//        root->print2D();
//    }
//    root->print2D();

    delete root;
    return 0;
}