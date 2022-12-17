//
// Created by Elad on 17/12/2022.
//

#ifndef DSH2_UNION_FIND_H
#define DSH2_UNION_FIND_H

#include "wet2util.h"

#include <memory>
#include <vector>

using namespace std;

#define null (-1)

typedef struct Node{
    int val;
    int set; int size;

    std::shared_ptr<Node> next = nullptr;

    Node(int val = 0, int set = null){
        this->val = val;
        this->set = set;
        size = 1;
    }
} Node;

class Union_Find {
    vector<shared_ptr<Node>> nodes;
    vector<shared_ptr<Node>> sets;
    StatusType unite(shared_ptr<Node> set1, shared_ptr<Node> set2);

public:
    Union_Find() = default;
    ~Union_Find() = default;
    Union_Find(Union_Find&) = delete;
    void operator=(Union_Find&) = delete;

    StatusType uniteSets(int set1, int set2);
    StatusType makeSet(int val, int set);
    StatusType find(int key);

    void print();
};


#endif //DSH2_UNION_FIND_H
