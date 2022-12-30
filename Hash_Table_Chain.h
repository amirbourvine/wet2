//
// Created by amirb on 24/12/2022.
//

#ifndef WET2_HASH_TABLE_CHAIN_H
#define WET2_HASH_TABLE_CHAIN_H

#include "wet2util.h"
#include "RankTree.h"
#include <iostream>
#include <memory>
#include <cmath>

using namespace std;

const static int INITIAL_SIZE = 7;

template <class T>//T-values
struct hash_obj{
    int key;
    T val;

    T& operator*(){
        return this->val;
    }
};

template <class T>
bool isLarger_hashobj(const hash_obj<T>& n1, const hash_obj<T>& n2){
    //the order inside each tree doesn't matter
    return true;
}

template <class T>//T-values
class Hash_Table_Chain{
private:
    RankTree<hash_obj<T>>* *arr;
    int size;
    int objNum;

    bool (*isEqual)(const T& t1, const T& t2);
    bool (*isEqual_hashobj)(const hash_obj<T>& n1, const hash_obj<T>& n2);


    StatusType increaseSize();

    int hash(int key, int size);
    StatusType insertAux(RankTree<hash_obj<T>>* *arr, int arr_size, hash_obj<T> obj);
    StatusType insert_tree_Aux(RankTree<hash_obj<T>>* *arr_, int arr_size, RankTree<hash_obj<T>>* tree);

    output_t<hash_obj<T>> getAux(RankTree<hash_obj<T>>* *arr, int arr_size, const T& demo_val, int key);
    output_t<hash_obj<T>*> getAddr(RankTree<hash_obj<T>>* *arr_, int arr_size, const T& demo_val, int key);

    static double ALPHA(){return ((sqrt(5)-1)/2);}

public:
    explicit Hash_Table_Chain(bool (*isEqual)(const T& t1, const T& t2), bool (*isEqual_hashobj)(const hash_obj<T>& n1, const hash_obj<T>& n2));
    ~Hash_Table_Chain();
    StatusType insert(int key, const T& val);
    output_t<T> get(const T& demo_val, int key);

    StatusType swap(const T &t1, const T& t2, int key1, int key2);

    //to-delete
    void printHash();
    int getObjNum() const;
    int getSize() const;
    hash_obj<T>** returnNarrowedArray();
};

template<class T>
Hash_Table_Chain<T>::Hash_Table_Chain(bool (*isEqual)(const T& t1, const T& t2),
                                      bool (*isEqual_hashobj)(const hash_obj<T>& n1, const hash_obj<T>& n2))
        : size(INITIAL_SIZE), objNum(0), isEqual(isEqual), isEqual_hashobj(isEqual_hashobj){
    this->arr = new RankTree<hash_obj<T>>*[INITIAL_SIZE];
    for(int i = 0; i<this->size; i++){
        this->arr[i] = new RankTree<hash_obj<T>>(isLarger_hashobj, (this->isEqual_hashobj));
    }
}

template<class T>
Hash_Table_Chain<T>::~Hash_Table_Chain() {
    for(int i = 0; i<this->size; i++){
        delete this->arr[i];
    }
    delete[] arr;
}

template<class T>
StatusType Hash_Table_Chain<T>::increaseSize() {
    int new_size = this->size*2 + 1;
    auto* temp = new RankTree<hash_obj<T>>*[new_size];
    if(temp == nullptr){
        return StatusType::ALLOCATION_ERROR;
    }
    for(int i = 0; i<new_size; i++){
        temp[i] = new RankTree<hash_obj<T>>(isLarger_hashobj, this->isEqual_hashobj);
        if(temp[i] == nullptr){
            for(int j = 0; j<i; j++){
                delete temp[j];
            }
            delete[] temp;
            return StatusType::ALLOCATION_ERROR;
        }
    }
    StatusType st;
    for(int i = 0; i<this->size; i++){
        if(!(this->arr[i]== nullptr||this->arr[i]->isEmpty()))
            st = insert_tree_Aux(temp, new_size, this->arr[i]);
        if(st!=StatusType::SUCCESS){
            for(int j = 0; j<new_size; j++){
                delete temp[j];
            }
            delete[] temp;
            return st;
        }
    }
    for(int i = 0; i<this->size; i++){
        delete this->arr[i];
    }
    delete[] this->arr;
    this->arr = temp;
    this->size = new_size;

    return StatusType::SUCCESS;
}

template<class T>
int Hash_Table_Chain<T>::hash(int key, int arr_size) {
    double temp = (key*ALPHA());
    double waste;
    double frac = modf(temp, &waste);
    int h = floor(arr_size*frac);
    return h%arr_size;
}

template<class T>
StatusType Hash_Table_Chain<T>::insert_tree_Aux(RankTree<hash_obj<T>>* *arr_, int arr_size, RankTree<hash_obj<T>>* tree) {
    if(arr_==nullptr){
        return StatusType::INVALID_INPUT;
    }
    hash_obj<T>* *array = new hash_obj<T>*[tree->getSize()];
    tree->inorderToArr(array, tree->getSize());
    for(int i = 0; i<tree->getSize(); i++){
        StatusType st = insertAux(arr_, arr_size, *array[i]);
        if(st!=StatusType::SUCCESS) {
            delete[] array;
            return st;
        }
    }
    delete[] array;
    return StatusType::SUCCESS;
}

template<class T>
StatusType Hash_Table_Chain<T>::insertAux(RankTree<hash_obj<T>>* *arr_, int arr_size, hash_obj<T> obj) {
    if(arr_==nullptr){
        return StatusType::INVALID_INPUT;
    }
    StatusType st = arr_[hash(obj.key, arr_size)]->insert(obj);
    if(st!=StatusType::SUCCESS)
        return st;
    return StatusType::SUCCESS;
}

template<class T>
StatusType Hash_Table_Chain<T>::insert(int key, const T &val) {
    hash_obj<T> obj;
    obj.key = key;
    obj.val = val;

    StatusType st = insertAux(this->arr, this->size, obj);
    if(st != StatusType::SUCCESS)
        return st;

    this->objNum = this->objNum + 1;
    if(this->objNum == this->size){
        st = this->increaseSize();
        if(st != StatusType::SUCCESS)
            return st;
    }
    return StatusType::SUCCESS;
}

template<class T>
output_t<T> Hash_Table_Chain<T>::get(const T& demo_val, int key) {
    if(this->arr==nullptr){
        return StatusType::FAILURE;
    }
    output_t<hash_obj<T>> output = getAux(this->arr, this->size, demo_val, key);
    if(output.status()!=StatusType::SUCCESS)
        return output.status();
    return output.ans().val;
}

template<class T>
output_t<hash_obj<T>> Hash_Table_Chain<T>::getAux(RankTree<hash_obj<T>>* *arr_, int arr_size, const T& demo_val, int key) {
    if(arr_==nullptr){
        return StatusType::INVALID_INPUT;
    }
    hash_obj<T> obj;
    obj.val = demo_val;
    obj.key = key;
    int index = hash(key, arr_size);
    output_t<RankNode<hash_obj<T>>*> output = arr_[index]->find_no_order(obj);

    if(output.status()!=StatusType::SUCCESS)
        return output.status();

    return *(output.ans()->getKey().ans());
}

template<class T>
output_t<hash_obj<T>*> Hash_Table_Chain<T>::getAddr(RankTree<hash_obj<T>>* *arr_, int arr_size, const T& demo_val, int key) {
    if(arr_==nullptr){
        return StatusType::INVALID_INPUT;
    }
    hash_obj<T> obj;
    obj.val = demo_val;
    obj.key = key;
    output_t<RankNode<hash_obj<T>>*> output = arr_[hash(key, arr_size)]->find_no_order(obj);

    if(output.status()!=StatusType::SUCCESS)
        return output.status();

    return output.ans()->getKey().ans();
}

template<class T>
void Hash_Table_Chain<T>::printHash() {
    cout << "ARR_SIZE: " << this->size <<endl;
    cout << "NUM_OBJ: " << this->objNum <<endl;
    cout << "ARR:" <<endl;
    for(int i = 0; i<this->size; i++){
        if(!this->arr[i]->isEmpty()) {
            cout << "*****************INDEX " << i << ":*****************" << endl;
            this->arr[i]->print2D();
        }
    }
    cout<<endl;
}




template<class T>
int Hash_Table_Chain<T>::getObjNum() const{
    return this->objNum;
}

template<class T>
int Hash_Table_Chain<T>::getSize() const{
    return this->size;
}

template<class T>
StatusType Hash_Table_Chain<T>::swap(const T &t1, const T& t2, int key1, int key2) {
    output_t<hash_obj<T>> output1 = this->getAux(this->arr, this->size, t1, key1);
    if(output1.status()!=StatusType::SUCCESS){
        return output1.status();
    }
    hash_obj<T> obj1 = output1.ans();

    output_t<hash_obj<T>> output2 = this->getAux(this->arr, this->size, t2, key2);
    if(output2.status()!=StatusType::SUCCESS){
        return output2.status();
    }
    hash_obj<T> obj2 = output2.ans();

    output_t<hash_obj<T>*> output11 = this->getAddr(this->arr, this->size, t1, key1);
    if(output11.status()!=StatusType::SUCCESS){
        return output11.status();
    }
    hash_obj<T>* addr1 = output11.ans();

    output_t<hash_obj<T>*> output21 = this->getAddr(this->arr, this->size, t2, key2);
    if(output21.status()!=StatusType::SUCCESS){
        return output21.status();
    }
    hash_obj<T>* addr2 = output21.ans();

    *addr1 = obj2;
    *addr2 = obj1;

    return StatusType::SUCCESS;
}

template<class T>
hash_obj<T>** Hash_Table_Chain<T>::returnNarrowedArray() {
    hash_obj<T>* *array = new hash_obj<T>*[this->objNum];
    int index = 0;
    int i = 0;
    while(index < this->objNum){
        this->arr[i]->inorderToArr(array+index, this->arr[i]->getSize());
        index += this->arr[i]->getSize();
        i++;
    }
    return array;
}

#endif //WET2_HASH_TABLE_CHAIN_H
