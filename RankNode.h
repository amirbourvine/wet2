//
// Created by amirb on 19/12/2022.
//

#ifndef DSH2_RANKNODE_H
#define DSH2_RANKNODE_H

#include "AVLNode.h"

template <class T>
class RankNode : public AVLNode<T>{
private:
    int val;


    void updateVal(RankNode<T>* root);

    output_t<RankNode<T>*> LLRotation(RankNode<T>* root) override;
    output_t<RankNode<T>*> RRRotation(RankNode<T>* root) override;
    output_t<RankNode<T>*> LRRotation(RankNode<T>* root) override;
    output_t<RankNode<T>*> RLRotation(RankNode<T>* root) override;


public:
    RankNode(bool (*isLarger)(const T& t1, const T& t2), bool (*isEqual)(const T& pt1, const T& pt2));
    explicit RankNode(const T& key, bool (*isLarger)(const T& t1, const T& t2), bool (*isEqual)(const T& t1, const T& t2));
    RankNode(const RankNode<T>& other) = delete;
    RankNode<T>& operator=(const RankNode<T>& other) = delete;
    virtual ~RankNode() = default;

    output_t<RankNode<T>*> insert(const T& val) override;
    output_t<RankNode<T>*> remove(const T& val) override;
};

template<class T>
RankNode<T>::RankNode(bool (*isLarger)(const T &, const T &), bool (*isEqual)(const T &, const T &))
        :AVLNode<T>(isLarger, isEqual), val(1){
}

template<class T>
RankNode<T>::RankNode(const T &key, bool (*isLarger)(const T &, const T &), bool (*isEqual)(const T &, const T &))
        :AVLNode<T>(key, isLarger, isEqual), val(1){
}

template<class T>
void RankNode<T>::updateVal(RankNode<T> *root) {
    if(root== nullptr){
        return;
    }
    RankNode<T>* left = root->left;
    RankNode<T>* right = root->right;

    if(left == nullptr && right == nullptr){
        root->val = 1;
    }
    if(left != nullptr && right == nullptr){
        root->val = 1 + left->val;
    }
    if(left != nullptr && right != nullptr){
        root->val = 1 + left->val + right->val;
    }
    if(left != nullptr && right == nullptr){
        root->val = 1 + right->val;
    }
}


template<class T>
output_t<RankNode<T> *> RankNode<T>::LLRotation(RankNode<T> *root) {
    output_t<AVLNode<T> *> out = AVLNode<T>::LLRotation(root);
    if(out.status()!=StatusType::SUCCESS){
        return out.status();
    }
    updateVal(out.ans()->right);
    updateVal(out.ans());
    return out.ans();
}


template<class T>
output_t<RankNode<T> *> RankNode<T>::RRRotation(RankNode<T> *root) {
    output_t<AVLNode<T> *> out = AVLNode<T>::RRRotation(root);
    if(out.status()!=StatusType::SUCCESS){
        return out.status();
    }
    updateVal(out.ans()->left);
    updateVal(out.ans());
    return out.ans();
}

template<class T>
output_t<RankNode<T> *> RankNode<T>::LRRotation(RankNode<T> *root) {
    output_t<AVLNode<T> *> out = AVLNode<T>::LRRotation(root);
    if(out.status()!=StatusType::SUCCESS){
        return out.status();
    }
    updateVal(out.ans()->left);
    updateVal(out.ans()->right);
    updateVal(out.ans());
    return out.ans();
}

template<class T>
output_t<RankNode<T> *> RankNode<T>::RLRotation(RankNode<T> *root) {
    output_t<AVLNode<T> *> out = AVLNode<T>::RLRotation(root);
    if(out.status()!=StatusType::SUCCESS){
        return out.status();
    }
    updateVal(out.ans()->left);
    updateVal(out.ans()->right);
    updateVal(out.ans());
    return out.ans();
}


#endif //DSH2_RANKNODE_H
