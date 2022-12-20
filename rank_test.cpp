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
    for(int i = 0; i<10; i++){
        root->insert(i+1);
    }
    root->print2D();
    cout<<"********************************************************************"<<endl;

    StatusType st = root->remove(8);
    if(st!=StatusType::SUCCESS){
        cout<<"failure"<<endl;
    }
    else{
        root->print2D();
        cout<<"********************************************************************"<<endl;
    }

    st = root->remove(7);
    if(st!=StatusType::SUCCESS){
        cout<<"failure"<<endl;
    }
    else{
        root->print2D();
        cout<<"********************************************************************"<<endl;
    }
    st = root->remove(4);
    if(st!=StatusType::SUCCESS){
        cout<<"failure"<<endl;
    }
    else{
        root->print2D();
         cout<<"********************************************************************"<<endl;
    }
    st = root->remove(1);
    if(st!=StatusType::SUCCESS){
        cout<<"failure"<<endl;
    }
    else{
        root->print2D();
        cout<<"********************************************************************"<<endl;
    }


    delete root;
    return 0;
}