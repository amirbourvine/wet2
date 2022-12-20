//
// Created by amirb on 20/12/2022.
//
#include "AVLTree.h"

bool isLarger(const int& x, const int& y){
    return x>y;
}

bool isEqual(const int& x, const int& y){
    return x==y;
}

int main(){
    AVLTree<int>* root = new AVLTree<int>(isLarger, isEqual);
    for(int i = 0; i<20; i++){
        root->insert(i);
    }
    root->print2D();
    cout<<"********************************************************************"<<endl;

    delete root;
    return 0;
}