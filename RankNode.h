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

    output_t<AVLNode<T>*> LLRotation(AVLNode<T>* root) override;
    output_t<AVLNode<T>*> RRRotation(AVLNode<T>* root) override;
    output_t<AVLNode<T>*> LRRotation(AVLNode<T>* root) override;
    output_t<AVLNode<T>*> RLRotation(AVLNode<T>* root) override;

    AVLNode<T>* makeNode(const T& val) override;
    void updateDuringInsert(AVLNode<T>* node, AVLNode<T>* p) override;
    void updateDuringRemove(AVLNode<T>* node) override;
public:
    RankNode(bool (*isLarger)(const T& t1, const T& t2), bool (*isEqual)(const T& pt1, const T& pt2));
    explicit RankNode(const T& key, bool (*isLarger)(const T& t1, const T& t2), bool (*isEqual)(const T& t1, const T& t2));
    RankNode(const RankNode<T>& other) = delete;
    RankNode<T>& operator=(const RankNode<T>& other) = delete;
    virtual ~RankNode() = default;

    output_t<int> rank(const T &value);
    output_t<int> rankaux(RankNode<T>* root, const T &value);

    //to delete:
    void print2DUtil(AVLNode<T>* root, int space) override;
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
output_t<AVLNode<T> *> RankNode<T>::LLRotation(AVLNode<T> *root) {
    output_t<AVLNode<T> *> out = AVLNode<T>::LLRotation(root);
    if(out.status()!=StatusType::SUCCESS){
        return out.status();
    }
    updateVal(out.ans()->right);
    updateVal(out.ans());
    return out.ans();
}

template<class T>
output_t<AVLNode<T> *> RankNode<T>::RRRotation(AVLNode<T> *root) {
    output_t<AVLNode<T> *> out = AVLNode<T>::RRRotation(root);
    if(out.status()!=StatusType::SUCCESS){
        return out.status();
    }
    updateVal(out.ans()->left);
    updateVal(out.ans());
    return out.ans();
}

template<class T>
output_t<AVLNode<T> *> RankNode<T>::LRRotation(AVLNode<T> *root) {
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
output_t<AVLNode<T> *> RankNode<T>::RLRotation(AVLNode<T> *root) {
    output_t<AVLNode<T> *> out = AVLNode<T>::RLRotation(root);
    if(out.status()!=StatusType::SUCCESS){
        return out.status();
    }
    updateVal(out.ans()->left);
    updateVal(out.ans()->right);
    updateVal(out.ans());
    return out.ans();
}

template<class T>
AVLNode<T> *RankNode<T>::makeNode(const T &value) {
    return (new RankNode<T>(value, this->isLarger, this->isEqual));
}

template<class T>
void RankNode<T>::updateDuringInsert(AVLNode<T> *node, AVLNode<T> *p) {
    AVLNode<T>::updateDuringInsert(node, p);
    updateVal(p);
}

template<class T>
void RankNode<T>::updateDuringRemove(AVLNode<T> *node) {
    AVLNode<T>::updateDuringRemove(node);
    updateVal(node);
}

template<class T>
output_t<int> RankNode<T>::rankaux(RankNode<T>* root, const T &value) {
    if(root == nullptr){
        return StatusType::FAILURE;
    }
    if(root->isEmpty){
        return StatusType::FAILURE;
    }
    if(this->isEqual(value, root->key)){
        if(root->left == nullptr)
            return 1;
        else
            return 1 + root->left->val;
    }
    if(this->isLarger(root->key,value)){
        return rankaux(value, root->left);
    }
    else{
        if(root->left == nullptr)
            return rankaux(value, root->right) + 1;
        else
            return rankaux(value, root->right) + 1 + root->left->val;
    }
}

template<class T>
output_t<int> RankNode<T>::rank(const T &value) {
    return rankaux(this, value);
}

template<class T>
void RankNode<T>::print2DUtil(AVLNode<T> *root, int space) {
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
    cout << *t << ", h:" << root->h << ", val:"<< root->val << "\n";

    // Process left child
    print2DUtil(root->left, space);
}


#endif //DSH2_RANKNODE_H
