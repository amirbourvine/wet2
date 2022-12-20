//
// Created by amirb on 24/11/2022.
//

#ifndef DS_WET1_AVLTREE_H
#define DS_WET1_AVLTREE_H

#include "wet2util.h"
#include "AVLNode.h"
#include <iostream>
#include <exception>
using namespace std;

template <class T>
class AVLTree{
private:
    AVLNode<T>* root;


public:
    AVLTree(bool (*isLarger)(const T& t1, const T& t2), bool (*isEqual)(const T& pt1, const T& pt2));
    explicit AVLTree(const T& key, bool (*isLarger)(const T& t1, const T& t2), bool (*isEqual)(const T& t1, const T& t2));
    AVLTree(const AVLTree<T>& other) = delete;
    AVLTree<T>& operator=(const AVLTree<T>& other) = delete;
    ~AVLTree();

    output_t<bool> isLeaf();
    output_t<T*> getKey();
    output_t<int> getBF();
    output_t<AVLNode<T>*> find(const T& val);

    StatusType insert(const T& val);
    StatusType remove(const T& val);
    void inorder(void (*pFunction)(T& t));
    template<class S>
    void inorder(void (*pFunction)(T& t, S& s), S& s);
    void inorderToArr(T* *arr, int size);
    void inorderToArrInRange(T* *arr, int size, bool (*pFunction)(const T& t, int min, int max), int min, int max);
    int inRangeAmount(bool (*pFunction)(const T& t, int min, int max), int min, int max);

    void unite(AVLTree<T>* other);
    AVLNode<T>* findMax();
    output_t<AVLNode<T>*> findAbove(const T& val);
    output_t<AVLNode<T>*> findUnder(const T& val);

    int getSize();


    //to delete:
    void print2D();
    AVLNode<T>* getRight();
    AVLNode<T>* getLeft();
    AVLNode<T>* getUp();
    int getH();
};

template<class T>
AVLTree<T>::AVLTree(bool (*isLarger)(const T& t1, const T& t2), bool (*isEqual)(const T& t1, const T& t2)) {
    this->root = new AVLNode<T>(isLarger, isEqual);
}

template<class T>
AVLTree<T>::AVLTree(const T& key, bool (*isLarger)(const T& t1, const T& t2), bool (*isEqual)(const T& t1, const T& t2)) {
    this->root = new AVLNode<T>(key,isLarger, isEqual);
}

template<class T>
AVLTree<T>::~AVLTree(){
    delete this->root;
}

template<class T>
output_t<bool> AVLTree<T>::isLeaf(){
    return root->isLeaf();
}

template<class T>
output_t<T*> AVLTree<T>::getKey() {
    return root->getKey();
}

template<class T>
output_t<int> AVLTree<T>::getBF() {
    return root->getBF();
}

template<class T>
output_t<AVLNode<T>*> AVLTree<T>::find(const T &val) {
    return root->find(val);
}

template<class T>
void AVLTree<T>::print2D() {
    root->print2D();
}

template<class T>
AVLNode<T> *AVLTree<T>::getLeft() {
    return root->getLeft();
}

template<class T>
AVLNode<T> *AVLTree<T>::getRight() {
    return root->getRight();
}

template<class T>
AVLNode<T> *AVLTree<T>::getUp() {
    return root->getUp();
}

template<class T>
int AVLTree<T>::getH() {
    return root->getH();
}

template<class T>
StatusType AVLTree<T>::insert(const T &val) {
    output_t<AVLNode<T>*> output = this->root->insert(val);
    this->root = output.ans();
    return output.status();
}

template<class T>
StatusType AVLTree<T>::remove(const T &val) {
    output_t<AVLNode<T>*> output = this->root->remove(val);
    if(output.status()==StatusType::SUCCESS)
        this->root = output.ans();
    return output.status();
}

template<class T>
void AVLTree<T>::inorder(void (*pFunction)(T& t)) {
    this->root->inorder(this->root, pFunction);
}

template<class T>
void AVLTree<T>::inorderToArr(T **arr, int size) {
    this->root->inorderToArr(this->root, arr, size, 0);
}

template<class T>
void AVLTree<T>::inorderToArrInRange(T* *arr, int size,
                         bool (*pFunction)(const T& t, int min, int max), int min, int max){
    this->root->inorderToArrInRange(this->root, arr, size, 0, pFunction, min, max);
}

template<class T>
int AVLTree<T>::inRangeAmount(bool (*pFunction)(const T& t, int min, int max), int min, int max){
    return this->root->inRangeAmount(this->root, pFunction, 0, min, max);
}

template<class T>
AVLNode<T> *AVLTree<T>::findMax() {
    return this->root->findMax();
}

template<class T>
int AVLTree<T>::getSize() {
    return this->root->getSize(this->root);
}

template<class T>
void AVLTree<T>::unite(AVLTree<T> *other) {
    AVLNode<T>* new_root = this->root->unite(other->root);
    delete this->root;
    this->root = new_root;
}

template<class T>
output_t<AVLNode<T> *> AVLTree<T>::findAbove(const T &val) {
    return this->root->findAbove(this->root, val);
}

template<class T>
output_t<AVLNode<T> *> AVLTree<T>::findUnder(const T &val) {
    return this->root->findUnder(this->root, val);
}

template<class T>
template<class S>
void AVLTree<T>::inorder(void (*pFunction)(T &, S &), S& s) {
    this->root->template inorder(this->root,pFunction, s);
}


#endif //DS_WET1_AVLTREE_H
