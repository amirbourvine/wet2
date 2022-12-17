//
// Created by amirb on 17/12/2022.
//

#ifndef DSH2_HASH_TABLE_H
#define DSH2_HASH_TABLE_H

#include "wet2util.h"
#include "Dynamic_Array.h"
template <class T>//T-values
class Hash_Table{
private:
    Dynamic_Array<T> arr;
    bool (*isEmpty)(const T& val);
    bool (*isEqual)(const T& t1, const T& t2);

public:
    StatusType Insert(int key, const T& val);
    StatusType Delete(int key);
    output_t<const T&> get(int key);
};

#endif //DSH2_HASH_TABLE_H
