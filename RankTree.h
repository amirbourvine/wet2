//
// Created by amirb on 20/12/2022.
//

#ifndef WET2_RANKTREE_H
#define WET2_RANKTREE_H

#include "RankNode.h"

template<class T>
class RankTree{
private:
    RankNode<T>* root;
    int size;
public:
    RankTree(bool (*isLarger)(const T& t1, const T& t2), bool (*isEqual)(const T& pt1, const T& pt2));
    explicit RankTree(const T& key, bool (*isLarger)(const T& t1, const T& t2), bool (*isEqual)(const T& t1, const T& t2));
    RankTree(const RankTree<T>& other) = delete;
    RankTree<T>& operator=(RankTree<T> *other) = delete;
    ~RankTree();

    output_t<bool> isLeaf();
    output_t<T*> getKey();
    output_t<int> getBF();

    output_t<RankNode<T>*> find(const T& val);
    output_t<RankNode<T>*> find_no_order(const T& val);

    StatusType insert(const T& val);
    StatusType remove(const T& val);

    output_t<int> rank(const T &value);
    output_t<shared_ptr<T>> getIthRanked(int i);

    bool isEmpty(){ return this->size==0;}

    int inorderToArr(T **arr, int size_);
    int getSize(){return this->size;}
};

template<class T>
RankTree<T>::RankTree(bool (*isLarger)(const T& t1, const T& t2), bool (*isEqual)(const T& t1, const T& t2)) : size(0) {
    this->root = new RankNode<T>(isLarger, isEqual);
}

template<class T>
RankTree<T>::RankTree(const T& key, bool (*isLarger)(const T& t1, const T& t2), bool (*isEqual)(const T& t1, const T& t2)) : size(1) {
    this->root = new RankNode<T>(key,isLarger, isEqual);
}

template<class T>
RankTree<T>::~RankTree(){
    delete this->root;
}

template<class T>
output_t<bool> RankTree<T>::isLeaf(){
    return root->isLeaf();
}

template<class T>
output_t<T*> RankTree<T>::getKey() {
    return root->getKey();
}

template<class T>
output_t<int> RankTree<T>::getBF() {
    return root->getBF();
}

template<class T>
output_t<RankNode<T>*> RankTree<T>::find(const T &val) {
    return root->find(val);
}

template<class T>
StatusType RankTree<T>::insert(const T &val) {
    output_t<RankNode<T>*> output = this->root->insert(val);
    if(output.status()==StatusType::SUCCESS) {
        this->root = output.ans();
        size++;
    }
    return output.status();
}

template<class T>
StatusType RankTree<T>::remove(const T &val) {
    output_t<RankNode<T>*> output = this->root->remove(val);
    if(output.status()==StatusType::SUCCESS) {
        this->root = output.ans();
        size--;
    }
    return output.status();
}

template<class T>
output_t<int> RankTree<T>::rank(const T &value) {
    return this->root->rank(value);
}

template<class T>
output_t<shared_ptr<T>> RankTree<T>::getIthRanked(int i) {
    if(i<0||i>=this->size)
        return StatusType::FAILURE;
    return this->root->getIthRanked(i);
}

template<class T>
int RankTree<T>::inorderToArr(T **arr, int size_) {
    return this->root->inorderToArr(this->root, arr, size_, 0);
}

template<class T>
output_t<RankNode<T> *> RankTree<T>::find_no_order(const T &val) {
    return this->root->find_no_order(val);
}


#endif //WET2_RANKTREE_H
