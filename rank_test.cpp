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
    st = root->remove(1);
    if(st!=StatusType::SUCCESS){
        cout<<"failure"<<endl;
    }
    else{
        root->print2D();
        cout<<"********************************************************************"<<endl;
    }
    root->insert(1);
    root->print2D();
    cout<<"********************************************************************"<<endl;

    output_t<RankNode<int>*> output = root->find(9);
    if(output.status()!=StatusType::SUCCESS){
        cout<<"failure"<<endl;
    }
    else{
        output.ans()->print2D();
        cout<<"********************************************************************"<<endl;
    }
    cout<<"****************************RANK*******************************"<<endl;
    output_t<int> out = root->rank(1);
    if(out.status()==StatusType::SUCCESS)
        cout<<"RANK: " << out.ans()<<endl;
    else
        cout<<"FAILURE"<<endl;

    cout<<"****************************GET FROM RANK*******************************"<<endl;
    root->print2D();

    output_t<shared_ptr<int>> out1 = root->getIthRanked(2);
    if(out1.status()==StatusType::SUCCESS)
        cout<<"ITH RANKED: " << *(out1.ans())<<endl;
    else
        cout<<"FAILURE"<<endl;


    delete root;
    return 0;
}