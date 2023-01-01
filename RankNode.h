//
// Created by amirb on 19/12/2022.
//

#ifndef DSH2_RANKNODE_H
#define DSH2_RANKNODE_H

#include "wet2util.h"
#include <iostream>
#include <memory>

using namespace std;

#define COUNT 10
#define ERROR (-1)

template <class T>
class RankNode {
private:
    T key;
    RankNode<T>* left;
    RankNode<T>* right;
    RankNode<T>* up;
    int val;
    int h;//height
    bool isEmpty;
    bool (*isEqual)(const T& t1, const T& t2);//true if t1==t2
    bool (*isLarger)(const T& t1, const T& t2);//true if t1>t2

    output_t<RankNode<T>*> insertaux(RankNode<T>* to_insert, RankNode<T> *root);
    output_t<RankNode<T>*> findaux(const T& val, RankNode<T>* root);

    bool find_no_order_aux(const T &value, RankNode<T>* *res, RankNode<T>* root_);

    output_t<shared_ptr<T>> getIthRankedaux(RankNode<T>* root, int i);
    void updateH(RankNode<T>* root);
    void fixVal();
    void updateDuringInsert();
    void updateDuringRemove();
    RankNode<T>* makeNode(const T& val);


    RankNode<T>* removeLeaf(RankNode<T>* node);//return the bottom of the route
    RankNode<T>* removeRightChild(RankNode<T>* node);//return the bottom of the route
    RankNode<T>* removeLeftChild(RankNode<T>* node);//return the bottom of the route
    RankNode<T>* removeTwoChildren(RankNode<T>* node);//return the bottom of the route

    output_t<RankNode<T>*> LLRotation();
    output_t<RankNode<T>*> RRRotation();
    output_t<RankNode<T>*> LRRotation();
    output_t<RankNode<T>*> RLRotation();

    void transferInfo(RankNode<T>* from, RankNode<T>* to);

    int rankaux(RankNode<T>* root, const T &value);
public:
    RankNode(bool (*isLarger)(const T& t1, const T& t2), bool (*isEqual)(const T& pt1, const T& pt2));
    explicit RankNode(const T& key, bool (*isLarger)(const T& t1, const T& t2), bool (*isEqual)(const T& t1, const T& t2));
    RankNode(const RankNode<T>& other) = delete;
    RankNode<T>& operator=(const RankNode<T>& other) = delete;
    virtual ~RankNode();

    output_t<bool> isLeaf();
    output_t<T*> getKey();
    output_t<int> getBF();

    output_t<RankNode<T>*> find(const T& val);
    output_t<RankNode<T>*> insert(const T& val);
    output_t<RankNode<T>*> remove(const T& val);

    output_t<shared_ptr<T>> getIthRanked(int i);

    void updateVal();

    output_t<int> rank(const T &value);

    int inorderToArr(RankNode<T>* root_, T **arr, int size, int ind);
    output_t<RankNode<T>*> find_no_order(const T &value);

    //to delete:
    void print2DUtil(RankNode<T>* root, int space);
    void print2D();
    int getH();
    RankNode<T>* getRight();
    RankNode<T>* getLeft();
    RankNode<T>* getUp();
};

template<class T>
RankNode<T>::RankNode(bool (*isLarger)(const T &, const T &), bool (*isEqual)(const T &, const T &))
        : left(nullptr), right(nullptr), up(nullptr), val(1), h(0), isEmpty(true), isEqual(isEqual),
        isLarger(isLarger){
}

template<class T>
RankNode<T>::RankNode(const T &key, bool (*isLarger)(const T &, const T &), bool (*isEqual)(const T &, const T &))
        :key(key), left(nullptr), right(nullptr), up(nullptr), val(1), h(0), isEmpty(false), isEqual(isEqual),
         isLarger(isLarger){
}

template<class T>
RankNode<T>::~RankNode() {
    if(this == nullptr)
    {
        return;
    }
    delete this->left;
    delete this->right;
}

template<class T>
void RankNode<T>::updateVal() {
    if(this == nullptr){
        return;
    }

    if(this->left == nullptr && this->right == nullptr){
        this->val = 1;
    }
    if(this->left != nullptr && this->right == nullptr){
        this->val = 1 + this->left->val;
    }
    if(this->left != nullptr && this->right != nullptr){
        this->val = 1 + this->right->val + this->left->val;
    }
    if(this->left == nullptr && this->right != nullptr){
        this->val = 1 + this->right->val;
    }
}


template<class T>
output_t<RankNode<T> *> RankNode<T>::LLRotation() {
    if(this == nullptr){
        return StatusType::INVALID_INPUT;
    }
    if(this->left == nullptr){
        return StatusType::INVALID_INPUT;
    }
    if(this->left->left == nullptr){
        return StatusType::INVALID_INPUT;
    }
    RankNode<T>* B = this;
    RankNode<T>* A = this->left;
    RankNode<T>* AR = A->right;

    if(B->up!= nullptr) {
        if (B->up->left == B) {
            B->up->left = A;
        } else {
            B->up->right = A;
        }
    }
    A->up = B->up;
    A->right = B;
    B->up = A;
    B->left = AR;
    if(AR!= nullptr) {
        AR->up = B;
    }

    updateH(B);
    B->updateVal();

    updateH(A);
    A->updateVal();

    return A;
}

template<class T>
output_t<RankNode<T> *> RankNode<T>::RRRotation() {
    if(this == nullptr){
        return StatusType::INVALID_INPUT;
    }
    if(this->right == nullptr){
        return StatusType::INVALID_INPUT;
    }
    if(this->right->right == nullptr){
        return StatusType::INVALID_INPUT;
    }

    RankNode<T>* B = this;
    RankNode<T>* A = this->right;
    RankNode<T>* AL = A->left;

    if(B->up!= nullptr) {
        if (B->up->left == B) {
            B->up->left = A;
        } else {
            B->up->right = A;
        }
    }
    A->up = B->up;
    A->left = B;
    B->up = A;
    B->right = AL;
    if(AL!= nullptr) {
        AL->up = B;
    }

    updateH(B);
    B->updateVal();

    updateH(A);
    A->updateVal();

    return A;
}

template<class T>
output_t<RankNode<T> *> RankNode<T>::LRRotation() {
    if(this == nullptr){
        return StatusType::INVALID_INPUT;
    }
    if(this->left == nullptr){
        return StatusType::INVALID_INPUT;
    }
    if(this->left->right == nullptr){
        return StatusType::INVALID_INPUT;
    }

    RankNode<T>* C = this;
    RankNode<T>* A = C->left;
    RankNode<T>* B = A->right;
    RankNode<T>* BL = B->left;
    RankNode<T>* BR = B->right;

    if(C->up!= nullptr) {
        if (C->up->left == C) {
            C->up->left = B;
        } else {
            C->up->right = B;
        }
    }
    B->up = C->up;
    B->left = A;
    B->right = C;
    A->up = B;
    A->right = BL;
    if(BL!= nullptr) {
        BL->up = A;
    }
    C->up = B;
    C->left = BR;
    if(BR!= nullptr) {
        BR->up = C;
    }

    updateH(A);
    A->updateVal();

    updateH(C);
    C->updateVal();

    updateH(B);
    B->updateVal();

    return B;
}

template<class T>
output_t<RankNode<T> *> RankNode<T>::RLRotation() {
    if(this == nullptr){
        return StatusType::INVALID_INPUT;
    }
    if(this->right == nullptr){
        return StatusType::INVALID_INPUT;
    }
    if(this->right->left == nullptr){
        return StatusType::INVALID_INPUT;
    }

    RankNode<T>* C = this;
    RankNode<T>* A = C->right;
    RankNode<T>* B = A->left;
    RankNode<T>* BL = B->left;
    RankNode<T>* BR = B->right;

    if(C->up!= nullptr) {
        if (C->up->left == C) {
            C->up->left = B;
        } else {
            C->up->right = B;
        }
    }
    B->up = C->up;
    B->left = C;
    B->right = A;
    C->up = B;
    C->right = BL;
    if(BL!= nullptr) {
        BL->up = C;
    }
    A->up = B;
    A->left = BR;
    if(BR!= nullptr) {
        BR->up = A;
    }

    updateH(C);
    C->updateVal();

    updateH(A);
    A->updateVal();

    updateH(B);
    B->updateVal();

    return B;
}

template<class T>
RankNode<T> *RankNode<T>::makeNode(const T &value) {
    return (new RankNode<T>(value, this->isLarger, this->isEqual));
}

template<class T>
void RankNode<T>::updateDuringInsert() {
    this->up->h = this->h+1;
    this->up->updateVal();
}

template<class T>
void RankNode<T>::updateDuringRemove() {
    updateH(this);
    this->updateVal();
}

template<class T>
int RankNode<T>::rankaux(RankNode<T>* root, const T &value) {
    if(root == nullptr){
        return ERROR;
    }
    if(root->isEmpty){
        return ERROR;
    }
    if(this->isEqual(value, root->key)){
        if(root->left == nullptr)
            return 0;
        else
            return root->left->val;
    }
    if(this->isLarger(root->key,value)){
        return rankaux(root->left, value);
    }
    else{
        if(root->left == nullptr)
            return rankaux(root->right, value) + 1;
        else
            return rankaux(root->right, value) + 1 + root->left->val;
    }
}

template<class T>
output_t<int> RankNode<T>::rank(const T &value) {
    //first index: 0
    int num = rankaux(this, value);
    if(num==ERROR)
        return StatusType::FAILURE;
    return num;
}

//not compiling
template<class T>
void RankNode<T>::print2DUtil(RankNode<T> *root, int space) {
    // Base case
    if (root == nullptr)
        return;
    if(root->isEmpty)
        return;


    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    cout << endl;
    for (int i = COUNT; i < space; i++)
        cout << " ";
    //T t= root->key;
    //cout << t << ", h:" << root->h << ", val:"<< root->val << "\n";

    // Process left child
    print2DUtil(root->left, space);
}

template<class T>
output_t<bool> RankNode<T>::isLeaf() {
    if(this==nullptr){
        return StatusType::INVALID_INPUT;
    }
    if(this->right==nullptr && this->left==nullptr){
        return true;
    }
    else{
        return false;
    }
}

template<class T>
output_t<RankNode<T> *> RankNode<T>::insertaux(RankNode<T> *to_insert, RankNode<T> *root) {
    if(root == nullptr){
        return StatusType::FAILURE;
    }
    if(root->isEmpty){
        return StatusType::FAILURE;
    }
    if(this->isEqual(to_insert->key, root->key)){
        return StatusType::FAILURE;//no equal values in the tree
    }
    if(this->isLarger(root->key,to_insert->key)){
        if(root->left == nullptr){
            root->left = to_insert;
            root->left->up = root;
            return root->left;
        }
        else{
            return insertaux(to_insert, root->left);
        }
    }
    else{
        if(root->right == nullptr){
            root->right = to_insert;
            root->right->up = root;
            return root->right;
        }
        else{
            return insertaux(to_insert, root->right);
        }
    }
}

template<class T>
output_t<RankNode<T> *> RankNode<T>::findaux(const T &value, RankNode<T> *root) {
    if(root == nullptr){
        return StatusType::FAILURE;
    }
    if(root->isEmpty){
        return StatusType::FAILURE;
    }
    if(this->isEqual(value, root->key)){
        return root;
    }
    if(this->isLarger(root->key,value)){
        return findaux(value, root->left);
    }
    else{
        return findaux(value, root->right);
    }
}

template<class T>
void RankNode<T>::updateH(RankNode<T> *root) {
    if(root == nullptr){
        return;
    }
    if(root->left != nullptr && root->right != nullptr)
        root->h= max(root->left->h, root->right->h)+1;
    if(root->left!= nullptr && root->right == nullptr)
        root->h= root->left->h+1;
    if(root->left== nullptr && root->right != nullptr)
        root->h= root->right->h+1;
    if(root->left== nullptr && root->right == nullptr)
        root->h= 0;
}

template<class T>
RankNode<T> *RankNode<T>::removeLeaf(RankNode<T> *node) {
    RankNode<T>* temp = node->up;
    if(temp == nullptr){
        delete node;
        return nullptr;
    }
    if(node->up->left==node){
        node->up->left = nullptr;
        delete node;
    }
    else{
        node->up->right = nullptr;
        delete node;
    }
    return temp;
}

template<class T>
RankNode<T> *RankNode<T>::removeRightChild(RankNode<T> *node) {
    if(node->up == nullptr){
        RankNode<T>* keep = node->right;
        transferInfo(node->right, node);
        node->up = nullptr;

        keep->right = nullptr;
        keep->left = nullptr;

        delete keep;
        if(node->right!= nullptr)
            node->right->up = node;
        return node;
    }
    if(node->up->left==node){
        RankNode<T>* keep = node->up;
        node->up->left = node->right;
        node->up->left->up = node->up;

        node->right = nullptr;
        delete node;
        return keep;
    }
    else{
        RankNode<T>* keep = node->up;
        node->up->right = node->right;
        node->up->right->up = node->up;

        node->right = nullptr;
        delete node;
        return keep;
    }
}

template<class T>
RankNode<T> *RankNode<T>::removeLeftChild(RankNode<T> *node) {
    if(node->up == nullptr){
        RankNode<T>* keep = node->left;
        transferInfo(node->left, node);
        node->up = nullptr;

        keep->right = nullptr;
        keep->left = nullptr;

        delete keep;
        if(node->left!= nullptr)
            node->left->up = node;
        return node;
    }
    if(node->up->left==node){
        RankNode<T>* keep = node->up;
        node->up->left = node->left;
        node->up->left->up = node->up;

        node->left = nullptr;
        delete node;
        return keep;
    }
    else{
        RankNode<T>* keep = node->up;
        node->up->right = node->left;
        node->up->right->up = node->up;

        node->left = nullptr;
        node->left = nullptr;
        delete node;
        return keep;
    }
}

template<class T>
RankNode<T> *RankNode<T>::removeTwoChildren(RankNode<T> *node) {
    RankNode<T>* successor = node->right;
    while(successor->left != nullptr){
        successor = successor->left;
    }
    T& keep = node->key;
    node->key = successor->key;
    successor->key = keep;
    if(successor->right == nullptr){
        return removeLeaf(successor);
    }
    else{
        return removeRightChild(successor);
    }
}

template<class T>
void RankNode<T>::transferInfo(RankNode<T> *from, RankNode<T> *to) {
    to->key = from->key;//require operator= on T
    to->left = from->left;
    to->right = from->right;
    to->up = from->up;
    to->h = from->h;
    to->isEmpty = from->isEmpty;
    to->val = from->val;
}

template<class T>
output_t<T*> RankNode<T>::getKey() {
    if(this==nullptr){
        return StatusType::FAILURE;
    }
    if(this->isEmpty)
        return nullptr;

    return &(this->key);
}

template<class T>
output_t<int> RankNode<T>::getBF() {
    if(this == nullptr){
        return StatusType::INVALID_INPUT;
    }
    if(this->left == nullptr && this->right == nullptr){
        return 0;
    }
    if(this->left == nullptr && this->right != nullptr){
        return (-1-this->right->h);
    }
    if(this->left != nullptr && this->right == nullptr){
        return (this->left->h+1);
    }
    if(this->left != nullptr && this->right != nullptr){
        return (this->left->h-this->right->h);
    }
    return StatusType::FAILURE;//should not reach this code
}

template<class T>
output_t<RankNode<T> *> RankNode<T>::find(const T &value) {
    return findaux(value, this);
}

template<class T>
output_t<RankNode<T> *> RankNode<T>::insert(const T &value) {
    if(this->isEmpty){//case of empty tree
        this->key = value;
        this->isEmpty = false;
        return this;
    }

    RankNode<T>* to_insert = makeNode(value);

    output_t<RankNode<T>*> temp = insertaux(to_insert, this);
    if(temp.status()==StatusType::FAILURE){
        delete to_insert;
        return StatusType::FAILURE;
    }

    RankNode<T>* node = temp.ans();

    RankNode<T>* p;
    RankNode<T>* q;
    while(node!= nullptr && node!=this){
        p = node->up;
        if(p == nullptr){break;}
        if(p->h >= node->h+1){
            p->fixVal();
            return this;
        }
        node->updateDuringInsert();
        if(abs(p->getBF().ans())==2){
            if(p->getBF().ans()==2) {
                if (p->left->getBF().ans() == -1) {
                    q = p->LRRotation().ans();
                    if(q->h>this->h) {
                        return q;
                    }
                    else {
                        this->fixVal();
                        return this;
                    }
                } else {
                    q = p->LLRotation().ans();
                    if(q->h>this->h)
                        return q;
                    else {
                        this->fixVal();
                        return this;
                    }
                }
            }
            if(p->getBF().ans()==-2){
                if(p->right->getBF().ans()==1){
                    q = p->RLRotation().ans();

                    if(q->h>this->h)
                        return q;
                    else {
                        this->fixVal();
                        return this;
                    }
                }
                else{
                    q = p->RRRotation().ans();
                    if(q->h>this->h)
                        return q;
                    else {
                        this->fixVal();
                        return this;
                    }
                }
            }
        }
        else{
            node = p;
        }
    }
    return this;
}

template<class T>
output_t<RankNode<T> *> RankNode<T>::remove(const T &value) {
    output_t<RankNode<T>*> output = find(value);
    if(output.status()!=StatusType::SUCCESS){
        return output.status();
    }
    RankNode<T>* node = output.ans();
    RankNode<T>* bottom;
    RankNode<T>* keep;

    if(node->right == nullptr && node->left == nullptr){
        if(node->up == nullptr){
            node->isEmpty = true;
            return node;
        }
        bottom = removeLeaf(node);
    }
    else {
        if (node->right != nullptr && node->left == nullptr) {
            bottom = removeRightChild(node);
        } else {
            if (node->right == nullptr && node->left != nullptr) {
                bottom = removeLeftChild(node);
            }
            else {
                if (node->right != nullptr && node->left != nullptr) {
                    bottom = removeTwoChildren(node);
                }
            }
        }
    }
    //***until here is step 1 of the algo***

    while(bottom!= nullptr){
        bottom->updateDuringRemove();
        if(abs(bottom->getBF().ans())==2){
            if(bottom->getBF().ans()==2) {
                if (bottom->left->getBF().ans() == -1) {
                    bottom = bottom->LRRotation().ans();
                } else {
                    bottom = bottom->LLRotation().ans();
                }
            }
            else{
                if(bottom->right->getBF().ans()==1){
                    bottom = bottom->RLRotation().ans();
                }
                else{
                    bottom = bottom->RRRotation().ans();
                }
            }
        }
        if(bottom!= nullptr) {
            keep = bottom;
            bottom = bottom->up;
        }
    }

    return keep;
}

template<class T>
int RankNode<T>::getH() {
    if(this== nullptr){
        return -1;
    }
    return this->h;
}

template<class T>
RankNode<T> *RankNode<T>::getRight() {
    if(this== nullptr){
        return nullptr;
    }
    return this->right;
}

template<class T>
RankNode<T> *RankNode<T>::getLeft() {
    if(this== nullptr){
        return nullptr;
    }
    return this->left;
}

template<class T>
RankNode<T> *RankNode<T>::getUp() {
    if(this== nullptr){
        return nullptr;
    }
    return this->up;
}

template<class T>
void RankNode<T>::print2D() {
    print2DUtil(this, 0);
}

template<class T>
void RankNode<T>::fixVal() {
    RankNode<T>* temp = this;
    while(temp != nullptr){
        temp->updateVal();
        temp = temp->up;
    }
}

template<class T>
output_t<shared_ptr<T>> RankNode<T>::getIthRanked(int i) {
    //first index:0
    return getIthRankedaux(this,i);
}

template<class T>
output_t<shared_ptr<T>> RankNode<T>::getIthRankedaux(RankNode<T>* root, int i) {
    if(root== nullptr){
        return StatusType::FAILURE;
    }
    if(root->isEmpty){
        return StatusType::FAILURE;
    }

    if(root->left == nullptr){
        if(i==0) {
            shared_ptr<T> ptr = make_shared<T>(root->key);
            return ptr;
        }
        return getIthRankedaux(root->right, i-1);
    }
    if (root->left->val == i) {
        shared_ptr<T> ptr = make_shared<T>(root->key);
        return ptr;
    }
    if (root->left->val > i)
        return getIthRankedaux(root->left, i);
    return getIthRankedaux(root->right, i-1-root->left->val);
}

template<class T>
int RankNode<T>::inorderToArr(RankNode<T> *root_, T **arr, int size, int ind) {
    if(root_ == nullptr){
        return ind;
    }

    ind = inorderToArr(root_->left, arr, size, ind);
    if(ind < size) {
        arr[ind] = &root_->key;
        ind++;
    }
    else{
        return ind;
    }

    return inorderToArr(root_->right, arr, size, ind);
}

template<class T>
bool RankNode<T>::find_no_order_aux(const T &value, RankNode<T>* *res, RankNode<T>* root_) {
    if(root_ == nullptr){
        return false;
    }
    if(root_->isEmpty){
        return false;
    }
    if(this->isEqual(value, root_->key)){
        *res = root_;
        return true;
    }
    return find_no_order_aux(value,res, root_->left) ||
    find_no_order_aux(value,res, root_->right);
}

template<class T>
output_t<RankNode<T>*> RankNode<T>::find_no_order(const T &value) {
    RankNode<T>* res;
   bool flag = this->find_no_order_aux(value, &res, this);
    if(!flag)
        return StatusType::FAILURE;
    return res;
}


#endif //DSH2_RANKNODE_H
