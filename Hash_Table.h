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

const static int INITIAL_SIZE = 7;


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
    output_t<hash_obj<T>> getAux(hash_obj<T> *arr, int arr_size, const T& demo_val, int key);
    output_t<hash_obj<T>*> getAddr(hash_obj<T> *arr_, int arr_size, const T& demo_val, int key);


    static double ALPHA(){return ((sqrt(5)-1)/2);};
public:
    explicit Hash_Table(bool (*isEqual)(const T& t1, const T& t2));
    ~Hash_Table();
    StatusType insert(int key, const T& val);
    output_t<T> get(const T& demo_val, int key);

    StatusType swap(const T &t1, const T& t2, int key1, int key2);

    //to-delete
    void printHash();
    T* returnNarrowedArray();
    T* returnArray();
    int getObjNum() const;
    int getSize() const;
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
    double temp = (key*ALPHA());
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
    output_t<hash_obj<T>> output = getAux(this->arr, this->size, demo_val, key);
    if(output.status()!=StatusType::SUCCESS)
        return output.status();
    return output.ans().val;
}

template<class T>
output_t<hash_obj<T>> Hash_Table<T>::getAux(hash_obj<T> *arr_, int arr_size, const T& demo_val, int key) {
    int iteration = 0;
    while(iteration<arr_size){
        if(this->isEqual(arr_[hash(key, arr_size, iteration)].val, demo_val)){
            return arr_[hash(key, arr_size, iteration)];
        }
        if(arr_[hash(key, arr_size, iteration)].val == T{}){
            return StatusType::FAILURE;
        }
        iteration++;
    }
    return StatusType::FAILURE;
}

template<class T>
output_t<hash_obj<T>*> Hash_Table<T>::getAddr(hash_obj<T> *arr_, int arr_size, const T& demo_val, int key) {
    int iteration = 0;
    while(iteration<arr_size){
        if(this->isEqual(arr_[hash(key, arr_size, iteration)].val, demo_val)){
            return &arr_[hash(key, arr_size, iteration)];
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
T* Hash_Table<T>::returnArray(){
    T* output(new T[this->size]);
    int count = 0;
    for(int i = 0; i < this->size; i++) {
        output[i] = this->arr[i].val;
    }
    return output;
}

template<class T>
int Hash_Table<T>::getObjNum() const{
    return objNum;
}

template<class T>
int Hash_Table<T>::getSize() const{
    return size;
}

template<class T>
StatusType Hash_Table<T>::swap(const T &t1, const T& t2, int key1, int key2) {
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


#endif //DSH2_HASH_TABLE_H
