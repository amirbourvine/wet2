//
// Created by amirb on 17/12/2022.
//

#ifndef DSH2_HASH_TABLE_H
#define DSH2_HASH_TABLE_H

#include "wet2util.h"
#include <iostream>
#include <memory>
#include <cmath>

using namespace std;

#define INITIAL_SIZE 7
#define C 2
#define ALPHA ((sqrt(5)-1)/2)


template <class T>//T-values
struct hash_obj{
    int key;
    T val;
};

template <class T>//T-values
class Hash_Table{
private:
    hash_obj<T>* arr;
    int size;
    int objNum;

    bool (*isEqual)(const T& t1, const T& t2);

    StatusType increaseSize();

    int hash(int key, int size, int iteration);
    StatusType insertAux(hash_obj<T> *arr, int arr_size, hash_obj<T> obj);
    output_t<T> getAux(hash_obj<T> *arr, int arr_size, const T& demo_val, int key);

public:
    explicit Hash_Table(bool (*isEqual)(const T& t1, const T& t2));
    ~Hash_Table();
    StatusType insert(int key, const T& val);
    output_t<T> get(const T& demo_val, int key);


    //to-delete
    void printHash();
    T* returnNarrowedArray();
    int getObjNum() const;
};

template<class T>
Hash_Table<T>::Hash_Table(bool (*isEqual)(const T& t1, const T& t2)) : size(INITIAL_SIZE), objNum(0), isEqual(isEqual){
    this->arr = new hash_obj<T>[INITIAL_SIZE];
    hash_obj<T> obj;
    obj.val = T{};
    obj.key = 0;
    for(int i = 0; i<INITIAL_SIZE; i++){
        this->arr[i] = obj;
    }
}

template<class T>
Hash_Table<T>::~Hash_Table() {
    delete[] arr;
}

template<class T>
StatusType Hash_Table<T>::increaseSize() {
    int new_size = this->size*2 + 1;
    hash_obj<T>* temp = new hash_obj<T>[new_size];
    if(temp == nullptr){
        return StatusType::ALLOCATION_ERROR;
    }
    hash_obj<T> obj;
    obj.val = T{};
    obj.key = 0;
    for(int i = 0; i<new_size; i++){
        temp[i] = obj;
    }
    StatusType st;
    for(int i = 0; i<this->size; i++){
        obj.key = this->arr[i].key;
        obj.val = this->arr[i].val;
        st = insertAux(temp, new_size, obj);
        if(st!=StatusType::SUCCESS){
            delete[] temp;
            return st;
        }
        obj.val = T{};
        obj.key = 0;
        this->arr[i] = obj;
    }
    delete[] this->arr;
    this->arr = temp;
    this->size = new_size;

    return StatusType::SUCCESS;
}

template<class T>
int Hash_Table<T>::hash(int key, int arr_size, int iteration) {
    double temp = (key*ALPHA);
    double waste;
    double frac = modf(temp, &waste);
    int h = floor(arr_size*frac);
    return (h+iteration)%arr_size;
}

template<class T>
StatusType Hash_Table<T>::insertAux(hash_obj<T> *arr_, int arr_size, hash_obj<T> obj) {
    if(arr_==nullptr){
        return StatusType::INVALID_INPUT;
    }
    int iteration = 0;
    while(iteration<arr_size){
        if(arr_[hash(obj.key, arr_size, iteration)].val == T{}){
            arr_[hash(obj.key, arr_size, iteration)] = obj;//require copy c'tor on T
            return StatusType::SUCCESS;
        }
        iteration++;
    }
    return StatusType::FAILURE;
}

template<class T>
StatusType Hash_Table<T>::insert(int key, const T &val) {
    hash_obj<T> obj;
    obj.key = key;
    obj.val = val;

    StatusType st = insertAux(this->arr, this->size, obj);
    if(st != StatusType::SUCCESS)
        return st;

    this->objNum = this->objNum + 1;
    if(this->objNum == this->size){
        st = this->increaseSize();
    }
    if(st != StatusType::SUCCESS)
        return st;
    return StatusType::SUCCESS;
}

template<class T>
output_t<T> Hash_Table<T>::get(const T& demo_val, int key) {
    if(this->arr==nullptr){
        return StatusType::FAILURE;
    }
    return getAux(this->arr, this->size, demo_val, key);
}

template<class T>
output_t<T> Hash_Table<T>::getAux(hash_obj<T> *arr_, int arr_size, const T& demo_val, int key) {
    int iteration = 0;
    while(iteration<arr_size){
        if(this->isEqual(arr_[hash(key, arr_size, iteration)].val, demo_val)){
            return arr_[hash(key, arr_size, iteration)].val;
        }
        if(arr_[hash(key, arr_size, iteration)].val == T{}){
            return StatusType::FAILURE;
        }
        iteration++;
    }
    return StatusType::FAILURE;
}

template<class T>
void Hash_Table<T>::printHash() {
    cout << "ARR_SIZE: " << this->size <<endl;
    cout << "NUM_OBJ: " << this->objNum <<endl;
    cout << "ARR:" <<endl;
    for(int i = 0; i<this->size; i++){
        cout<<this->arr[i].val<<",";
    }
    cout<<endl;
}
template<class T>
T* Hash_Table<T>::returnNarrowedArray(){
    T* output(new T[this->objNum]);
    int count = 0;
    for(int i = 0; i < this->size; i++) {
        if(this->arr[i].val != T{}) {
            output[count] = this->arr[i].val;
            count++;
        }
    }

    return output;
}

template<class T>
int Hash_Table<T>::getObjNum() const{
    return objNum;
}


#endif //DSH2_HASH_TABLE_H
