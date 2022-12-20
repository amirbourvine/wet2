//
// Created by amirb on 21/11/2022.
//

#ifndef DS_WET1_AVLNODE_H
#define DS_WET1_AVLNODE_H

#include "wet2util.h"
#include <iostream>
#include <memory>
#include <exception>

using namespace std;

#define COUNT 10

template <class T>
class AVLNode{
protected:
    T key;
    AVLNode<T>* left;
    AVLNode<T>* right;
    AVLNode<T>* up;
    int h;//height
    bool isEmpty;
    bool (*isLarger)(const T& t1, const T& t2);//true if t1>t2
    bool (*isEqual)(const T& t1, const T& t2);//true if t1==t2

    output_t<AVLNode<T>*> insertaux(AVLNode<T>* to_insert, AVLNode<T> *root);
    output_t<AVLNode<T>*> findaux(const T& val, AVLNode<T>* root);
    void updateH(AVLNode<T>* root, AVLNode<T>* left, AVLNode<T>* right);
    virtual void updateDuringInsert(AVLNode<T>* node, AVLNode<T>* p);
    virtual void updateDuringRemove(AVLNode<T>* node);
    virtual AVLNode<T>* makeNode(const T& val);

    AVLNode<T>* removeLeaf(AVLNode<T>* node);//return the bottom of the route
    AVLNode<T>* removeRightChild(AVLNode<T>* node);//return the bottom of the route
    AVLNode<T>* removeLeftChild(AVLNode<T>* node);//return the bottom of the route
    AVLNode<T>* removeTwoChildren(AVLNode<T>* node);//return the bottom of the route

    virtual output_t<AVLNode<T>*> LLRotation(AVLNode<T>* root);
    virtual output_t<AVLNode<T>*> RRRotation(AVLNode<T>* root);
    virtual output_t<AVLNode<T>*> LRRotation(AVLNode<T>* root);
    virtual output_t<AVLNode<T>*> RLRotation(AVLNode<T>* root);

    void mergeArrays(shared_ptr<T> *arr1, shared_ptr<T> *arr2, shared_ptr<T> *arr3, int size1, int size2);
    void transferInfo(AVLNode<T>* from, AVLNode<T>* to);
    AVLNode<T>* sortedArrayToBST(shared_ptr<T> *arr, int start, int end);

    void changeH(AVLNode<T>* node);

    AVLNode<T>* findAboveAux(AVLNode<T>* node, const T& val, AVLNode<T>* closest, AVLNode<T>* *search_finished);
    AVLNode<T>* findUnderAux(AVLNode<T>* node, const T& val, AVLNode<T>* closest, AVLNode<T>* *search_finished);
public:
    AVLNode(bool (*isLarger)(const T& t1, const T& t2), bool (*isEqual)(const T& pt1, const T& pt2));
    explicit AVLNode(const T& key, bool (*isLarger)(const T& t1, const T& t2), bool (*isEqual)(const T& t1, const T& t2));
    AVLNode(const AVLNode<T>& other) = delete;
    AVLNode<T>& operator=(const AVLNode<T>& other) = delete;
    virtual ~AVLNode();

    output_t<bool> isLeaf();
    output_t<T*> getKey();
    output_t<int> getBF();
    output_t<AVLNode<T>*> find(const T& val);

    output_t<AVLNode<T>*> insert(const T& val);
    virtual output_t<AVLNode<T>*> remove(const T& val);
    void inorder(AVLNode<T>* root, void (*pFunction)(T& t));
    template <class S>
    void inorder(AVLNode<T>* root, void (*pFunction)(T& t, S& s), S& s);
    int inorderToArr(AVLNode<T>* root, T* *arr, int size, int ind);

    AVLNode<T>* unite(AVLNode<T>* other);
    AVLNode<T>* findMax();
    AVLNode<T>* findMin();
    output_t<AVLNode<T>*> findAbove(AVLNode<T> *root, const T& val);//in case of receiving the largest, return the largest
    output_t<AVLNode<T>*> findUnder(AVLNode<T> *root, const T& val);//in case of receiving the smallest, return the smallest

    int getSize(AVLNode<T>* node);




    //to delete:
    void print2DUtil(AVLNode<T>* root, int space);
    void print2D();
    AVLNode<T>* getRight();
    AVLNode<T>* getLeft();
    AVLNode<T>* getUp();
    int getH();
};

template<class T>
AVLNode<T>::AVLNode(bool (*isLarger)(const T& t1, const T& t2), bool (*isEqual)(const T& t1, const T& t2)) : h(0), isEmpty(true){
    this->left = nullptr;
    this->right = nullptr;
    this->up = nullptr;
    this->isEqual = isEqual;
    this->isLarger = isLarger;
}

template<class T>
AVLNode<T>::AVLNode(const T& key, bool (*isLarger)(const T& t1, const T& t2), bool (*isEqual)(const T& t1, const T& t2)) : key(key),h(0),isEmpty(false){
    this->left = nullptr;
    this->right = nullptr;
    this->up = nullptr;
    this->isEqual = isEqual;
    this->isLarger = isLarger;
}

template<class T>
AVLNode<T>::~AVLNode() {
    if(this == nullptr)
    {
        return;
    }
    delete this->left;
    delete this->right;
}


template<class T>
output_t<bool> AVLNode<T>::isLeaf() {
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
output_t<T*> AVLNode<T>::getKey() {
    if(this==nullptr){
        return StatusType::INVALID_INPUT;
    }
    if(this->isEmpty)
        return nullptr;

    return &(this->key);
}

template<class T>
output_t<AVLNode<T>*> AVLNode<T>::find(const T& val) {
    return findaux(val, this);
}

template<class T>
output_t<AVLNode<T> *> AVLNode<T>::findaux(const T& val, AVLNode<T> *root) {
    if(root == nullptr){
        return StatusType::FAILURE;
    }
    if(root->isEmpty){
        return StatusType::FAILURE;
    }
    if(this->isEqual(val, root->key)){
        return root;
    }
    if(this->isLarger(root->key,val)){
        return findaux(val, root->left);
    }
    else{
        return findaux(val, root->right);
    }
}

template<class T>
output_t<AVLNode<T> *> AVLNode<T>::LLRotation(AVLNode<T> *root) {
    if(root == nullptr){
        return StatusType::INVALID_INPUT;
    }
    if(root->left == nullptr){
        return StatusType::INVALID_INPUT;
    }
    if(root->left->left == nullptr){
        return StatusType::INVALID_INPUT;
    }
    AVLNode<T>* B = root;
    AVLNode<T>* A = root->left;
    AVLNode<T>* AR = A->right;
    AVLNode<T>* BR = B->right;
    AVLNode<T>* AL = A->left;

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

    updateH(B, AR, BR);
    updateH(A,AL,B);

    return A;
}

template<class T>
output_t<AVLNode<T> *> AVLNode<T>::RRRotation(AVLNode<T> *root) {
    if(root == nullptr){
        return StatusType::INVALID_INPUT;
    }
    if(root->right == nullptr){
        return StatusType::INVALID_INPUT;
    }
    if(root->right->right == nullptr){
        return StatusType::INVALID_INPUT;
    }

    AVLNode<T>* B = root;
    AVLNode<T>* A = root->right;
    AVLNode<T>* AL = A->left;
    AVLNode<T>* AR = A->right;
    AVLNode<T>* BL = B->left;

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

    updateH(B, BL, AL);
    updateH(A,B,AR);


    return A;
}

template<class T>
output_t<AVLNode<T> *> AVLNode<T>::LRRotation(AVLNode<T> *root) {
    if(root == nullptr){
        return StatusType::INVALID_INPUT;
    }
    if(root->left == nullptr){
        return StatusType::INVALID_INPUT;
    }
    if(root->left->right == nullptr){
        return StatusType::INVALID_INPUT;
    }

    AVLNode<T>* C = root;
    AVLNode<T>* A = C->left;
    AVLNode<T>* B = A->right;
    AVLNode<T>* BL = B->left;
    AVLNode<T>* BR = B->right;
    AVLNode<T>* AL = A->left;
    AVLNode<T>* CR = C->right;

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

    updateH(A, AL, BL);
    updateH(C, BR, CR);
    updateH(B, A, C);

    return B;
}

template<class T>
output_t<AVLNode<T> *> AVLNode<T>::RLRotation(AVLNode<T> *root) {
    if(root == nullptr){
        return StatusType::INVALID_INPUT;
    }
    if(root->right == nullptr){
        return StatusType::INVALID_INPUT;
    }
    if(root->right->left == nullptr){
        return StatusType::INVALID_INPUT;
    }

    AVLNode<T>* C = root;
    AVLNode<T>* A = C->right;
    AVLNode<T>* B = A->left;
    AVLNode<T>* BL = B->left;
    AVLNode<T>* BR = B->right;
    AVLNode<T>* CL = C->left;
    AVLNode<T>* AR = A->right;

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

    updateH(C, CL, BL);
    updateH(A, BR, AR);
    updateH(B, C, A);

    return B;
}

template<class T>
void AVLNode<T>::updateDuringInsert(AVLNode<T>* node, AVLNode<T>* p){
    p->h = node->h+1;
}

template<class T>
void AVLNode<T>::updateDuringRemove(AVLNode<T>* node){
    updateH(node, node->left, node->right);
}

template<class T>
AVLNode<T>* AVLNode<T>::makeNode(const T& val) {
    return (new AVLNode<T>(val, this->isLarger, this->isEqual));
}

template<class T>
output_t<AVLNode<T>*> AVLNode<T>::insert(const T& val) {
    if(this->isEmpty){//case of empty tree
        this->key = val;
        this->isEmpty = false;
        return this;
    }

    AVLNode<T>* to_insert = makeNode(val);

    output_t<AVLNode<T>*> temp = insertaux(to_insert, this);
    if(temp.status()==StatusType::FAILURE){
        delete to_insert;
        return StatusType::FAILURE;
    }

    AVLNode<T>* node = temp.ans();

    AVLNode<T>* p;
    AVLNode<T>* q;
    while(node!= nullptr && node!=this){
        p = node->up;
        if(p == nullptr){break;}
        if(p->h >= node->h+1){
            return this;
        }
        updateDuringInsert(node, p);
        if(abs(p->getBF().ans())==2){
            if(p->getBF().ans()==2) {
                if (p->left->getBF().ans() == -1) {
                    q = LRRotation(p).ans();
                    if(q->h>this->h)
                        return q;
                    else
                        return this;
                } else {
                    q = LLRotation(p).ans();
                    if(q->h>this->h)
                        return q;
                    else
                        return this;
                }
            }
            if(p->getBF().ans()==-2){
                if(p->right->getBF().ans()==1){
                    q = RLRotation(p).ans();

                    if(q->h>this->h)
                        return q;
                    else
                        return this;
                }
                else{
                    q = RRRotation(p).ans();
                    if(q->h>this->h)
                        return q;
                    else
                        return this;
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
output_t<AVLNode<T>*> AVLNode<T>::insertaux(AVLNode<T>* to_insert, AVLNode<T> *root) {
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
output_t<int> AVLNode<T>::getBF() {
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
void AVLNode<T>::print2DUtil(AVLNode<T>* root, int space)
{
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
    T* t= root->getKey().ans();
    cout << *t << ", h:" << root->h << "\n";

    // Process left child
    print2DUtil(root->left, space);
}

template<class T>
void AVLNode<T>::print2D() {
    print2DUtil(this, 0);
}

template<class T>
AVLNode<T> *AVLNode<T>::getRight() {
    return this->right;
}

template<class T>
AVLNode<T> *AVLNode<T>::getLeft() {
    return this->left;
}

template<class T>
AVLNode<T> *AVLNode<T>::getUp() {
    return this->up;
}

template<class T>
int AVLNode<T>::getH() {
    return this->h;
}

template<class T>
void AVLNode<T>::updateH(AVLNode<T> *root, AVLNode<T> *leftt, AVLNode<T> *rightt) {
    if(leftt!= nullptr && rightt!= nullptr)
        root->h= max(leftt->h, rightt->h)+1;
    if(leftt!= nullptr && rightt == nullptr)
        root->h= leftt->h+1;
    if(leftt== nullptr && rightt != nullptr)
        root->h= rightt->h+1;
    if(leftt== nullptr && rightt == nullptr)
        root->h= 0;
}

template<class T>
output_t<AVLNode<T>*> AVLNode<T>::remove(const T &val) {
    output_t<AVLNode<T>*> output = find(val);
    if(output.status()!=StatusType::SUCCESS){
        return output.status();
    }
    AVLNode<T>* node = output.ans();
    AVLNode<T>* bottom;
    AVLNode<T>* keep;

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
        updateDuringRemove(bottom);
        if(abs(bottom->getBF().ans())==2){
            if(bottom->getBF().ans()==2) {
                if (bottom->left->getBF().ans() == -1) {
                    bottom = LRRotation(bottom).ans();
                } else {
                    bottom = LLRotation(bottom).ans();
                }
            }
            else{
                if(bottom->right->getBF().ans()==1){
                    bottom = RLRotation(bottom).ans();
                }
                else{
                    bottom = RRRotation(bottom).ans();
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
AVLNode<T> *AVLNode<T>::removeLeaf(AVLNode<T> *node) {
    AVLNode<T>* temp = node->up;
    if(temp== nullptr){
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
AVLNode<T> *AVLNode<T>::removeRightChild(AVLNode<T> *node) {
    if(node->up == nullptr){
        AVLNode<T>* keep = node->right;
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
        AVLNode<T>* keep = node->up;
        node->up->left = node->right;
        node->up->left->up = node->up;

        node->right = nullptr;
        delete node;
        return keep;
    }
    else{
        AVLNode<T>* keep = node->up;
        node->up->right = node->right;
        node->up->right->up = node->up;

        node->right = nullptr;
        delete node;
        return keep;
    }
}

template<class T>
void AVLNode<T>::transferInfo(AVLNode<T>* from, AVLNode<T>* to) {
    to->key = from->key;//require operator= on T
    to->left = from->left;
    to->right = from->right;
    to->up = from->up;
    to->h = from->h;
    to->isEmpty = from->isEmpty;
}

template<class T>
AVLNode<T> *AVLNode<T>::removeLeftChild(AVLNode<T> *node) {
    if(node->up == nullptr){
        AVLNode<T>* keep = node->left;
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
        AVLNode<T>* keep = node->up;
        node->up->left = node->left;
        node->up->left->up = node->up;

        node->left = nullptr;
        delete node;
        return keep;
    }
    else{
        AVLNode<T>* keep = node->up;
        node->up->right = node->left;
        node->up->right->up = node->up;

        node->left = nullptr;
        node->left = nullptr;
        delete node;
        return keep;
    }
}

template<class T>
AVLNode<T> *AVLNode<T>::removeTwoChildren(AVLNode<T> *node) {
    AVLNode<T>* successor = node->right;
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
void AVLNode<T>::inorder(AVLNode<T>* root, void (*pFunction)(T& t)){
    if(root == nullptr){
        return;
    }
    if(root->isEmpty){
        return;
    }

    inorder(root->left, pFunction);
    pFunction(root->key);
    inorder(root->right, pFunction);
}

template<class T>
int AVLNode<T>::inorderToArr(AVLNode<T> *root, T **arr, int size, int ind) {
    if(root == nullptr){
        return ind;
    }

    ind = inorderToArr(root->left, arr, size, ind);
    if(ind < size) {
        arr[ind] = &root->key;
        ind++;
    }
    else{
        return ind;
    }

    return inorderToArr(root->right, arr, size, ind);
}

template<class T>
AVLNode<T> *AVLNode<T>::findMax() {
    AVLNode<T>* node = this;
    while(node->right!= nullptr){
        node = node->right;
    }
    return node;
}

template<class T>
int AVLNode<T>::getSize(AVLNode<T> * node) {
    if(node == nullptr){
        return 0;
    }
    if(node->isEmpty){
        return 0;
    }
    return getSize(node->left)+ getSize(node->right)+1;
}

template<class T>
AVLNode<T>* AVLNode<T>::unite(AVLNode<T> *other) {
    int size1 = this->getSize(this);
    int size2 = other->getSize(other);
    T* *arr1 = new T*[size1];
    T* *arr2 = new T*[size2];
    this->inorderToArr(this,arr1, size1,0);
    other->inorderToArr(other,arr2, size2,0);

    shared_ptr<T> *arr2new = new shared_ptr<T>[size2];
    for(int i = 0; i<size2; i++){
        arr2new[i] = shared_ptr<T>(new T(*arr2[i]));//require copyCtor on T
        arr2[i] = nullptr;
    }
    delete[] arr2;

    shared_ptr<T> *arr1new = new shared_ptr<T>[size1];
    for(int i = 0; i<size1; i++){
        arr1new[i] = shared_ptr<T>(new T(*arr1[i]));//require copyCtor on T
        arr1[i] = nullptr;
    }
    delete[] arr1;


    shared_ptr<T> *arr3 = new shared_ptr<T>[size1+size2];
    mergeArrays(arr1new, arr2new, arr3, size1, size2);

    AVLNode<T>* node = sortedArrayToBST(arr3, 0, size1+size2-1);

    changeH(node);

    delete[] arr1new;
    delete[] arr2new;
    delete[] arr3;

    return node;
}

template<class T>
void AVLNode<T>::changeH(AVLNode<T>* node){
    if(node == nullptr){
        return;
    }
    if(node->isEmpty){
        node->h = 0;
        return;
    }

    changeH(node->left);
    changeH(node->right);
    updateH(node, node->left, node->right);

}
template<class T>
void AVLNode<T>::mergeArrays(shared_ptr<T> *arr1, shared_ptr<T> *arr2, shared_ptr<T> *arr3, int size1, int size2) {
    //we assume that there are no equal values, and that arr3 is large enough
    int num1=0,num2=0,num3=0;
    while(num1<size1&&num2<size2){
        if(this->isLarger(*arr1[num1], *arr2[num2])){
            arr3[num3] = arr2[num2];
            num3++;
            num2++;
        }
        else{
            arr3[num3] = arr1[num1];
            num3++;
            num1++;
        };
    }
    while(num1<size1){
        arr3[num3] = arr1[num1];
        num3++;
        num1++;
    }
    while(num2<size2){
        arr3[num3] = arr2[num2];
        num3++;
        num2++;
    }
}

template<class T>
AVLNode<T> *AVLNode<T>::sortedArrayToBST(shared_ptr<T> *arr, int start, int end) {
    if(start>end){
        return nullptr;
    }
    int mid = (start + end)/2;
    AVLNode<T>* node = new AVLNode<T>(*arr[mid], this->isLarger, this->isEqual);

    node->left = sortedArrayToBST(arr, start, mid-1);
    if(node->left!= nullptr)
        node->left->up = node;

    node->right = sortedArrayToBST(arr, mid+1, end);
    if(node->right!= nullptr)
        node->right->up = node;

    return node;
}

template<class T>
output_t<AVLNode<T>*> AVLNode<T>::findAbove(AVLNode<T> *root, const T& val) {//search in root for the node above val
    if(root == nullptr){
        return StatusType::INVALID_INPUT;
    }
    if(root->isEmpty){
        return StatusType::INVALID_INPUT;
    }
    if(this->isLarger(val, root->findMax()->key) || this->isEqual(val, root->findMax()->key)){
        return nullptr;
    }
    AVLNode<T>* search_finished;
    AVLNode<T>*  closest = findAboveAux(root, val, root->findMax(), &search_finished);
    if(search_finished == nullptr){
        return closest;
    }


    AVLNode<T>* temp = search_finished->right;
    if(temp == nullptr){
        return closest;
    }
    while(temp->left != nullptr){
        temp = temp->left;
    }
    if(temp == nullptr){
        return closest;
    }
    if(this->isLarger(temp->key,val) && this->isLarger(closest->key, temp->key)){
        return temp;
    }
    return closest;
}

template<class T>
AVLNode<T>* AVLNode<T>::findAboveAux(AVLNode<T> *node, const T& val, AVLNode<T> *closest, AVLNode<T>* *search_finished) {
    if(node == nullptr){
        *search_finished = nullptr;
        return closest;
    }
    if(node->isEmpty){
        *search_finished = nullptr;
        return closest;
    }
    //update closest
    if(this->isLarger(node->key,val) && this->isLarger(closest->key, node->key)){
        closest = node;
    }

    if(this->isEqual(val, node->key)){
        *search_finished = node;
        return closest;
    }
    if(this->isLarger(node->key,val)){
        return findAboveAux(node->left, val, closest, search_finished);
    }
    else{
        return findAboveAux(node->right, val, closest, search_finished);
    }
}

template<class T>
AVLNode<T> *
AVLNode<T>::findUnderAux(AVLNode<T> *node, const T &val, AVLNode<T> *closest, AVLNode<T> **search_finished) {
    if(node == nullptr){
        *search_finished = nullptr;
        return closest;
    }
    if(node->isEmpty){
        *search_finished = nullptr;
        return closest;
    }
    //update closest
    if(this->isLarger(val, node->key) && this->isLarger(node->key, closest->key)){
        closest = node;
    }

    if(this->isEqual(val, node->key)){
        *search_finished = node;
        return closest;
    }
    if(this->isLarger(node->key,val)){
        return findUnderAux(node->left, val, closest, search_finished);
    }
    else{
        return findUnderAux(node->right, val, closest, search_finished);
    }
}

template<class T>
output_t<AVLNode<T> *> AVLNode<T>::findUnder(AVLNode<T> *root, const T &val) {
    if(root == nullptr){
        return StatusType::INVALID_INPUT;
    }
    if(root->isEmpty){
        return StatusType::INVALID_INPUT;
    }
    if(this->isLarger(root->findMin()->key, val) || this->isEqual(root->findMin()->key, val)){
        return nullptr;
    }
    AVLNode<T>* search_finished;
    AVLNode<T>*  closest = findUnderAux(root, val, root->findMin(), &search_finished);
    if(search_finished == nullptr){
        return closest;
    }

    AVLNode<T>* temp = search_finished->left;
    if(temp == nullptr){
        return closest;
    }
    while(temp->right != nullptr){
        temp = temp->right;
    }
    if(temp == nullptr){
        return closest;
    }
    if(this->isLarger(val, temp->key) && this->isLarger(temp->key, closest->key)){
        return temp;
    }
    return closest;
}

template<class T>
AVLNode<T> *AVLNode<T>::findMin() {
    AVLNode<T>* node = this;
    while(node->left!= nullptr){
        node = node->left;
    }
    return node;
}

template<class T>
template<class S>
void AVLNode<T>::inorder(AVLNode<T> *root, void (*pFunction)(T &, S &), S& s) {
    if(root == nullptr){
        return;
    }
    if(root->isEmpty){
        return;
    }

    inorder(root->left, pFunction, s);
    pFunction(root->key, s);
    inorder(root->right, pFunction, s);
}

#endif //DS_WET1_AVLNODE_H
