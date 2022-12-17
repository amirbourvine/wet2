#ifndef DSH2_UNION_FIND_H
#define DSH2_UNION_FIND_H

#include "Team.h"

#include <memory>
#include <vector>

using namespace std;

#define null (-1)

typedef struct Node{
    shared_ptr<Player> player;
    shared_ptr<Team> team;

    std::shared_ptr<Node> next = nullptr;

    Node(shared_ptr<Player> player = nullptr, shared_ptr<Team> team = nullptr){
        this->player = player;
        this->team = team;
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

    StatusType uniteSets(int team1, int team2);
    StatusType makeSet(const shared_ptr<Player>&, const shared_ptr<Team>&);
    output_t<shared_ptr<Team>> find(int playerId);

    void print();
};


#endif //DSH2_UNION_FIND_H
