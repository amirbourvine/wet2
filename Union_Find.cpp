#include <algorithm>
#include <iostream>

#include "Union_Find.h"

StatusType Union_Find::unite(shared_ptr<Node> set1, shared_ptr<Node> set2){
    //change to key1 and key2 and size comparison
    sets.erase(std::find(sets.begin(), sets.end(), set1));

    set1->team = nullptr;
    set1->next = set2;

    return StatusType::SUCCESS;
}

StatusType Union_Find::uniteSets(int set1, int set2){
    if(set1 == set2)
        return StatusType::FAILURE;

    shared_ptr<Node> set1ptr = nullptr;
    for(auto it : sets){
        if(it->team->getTeamId() == set1)
            set1ptr = it;
    }
    if(set1ptr == nullptr)
        return StatusType::FAILURE;

    shared_ptr<Node> set2ptr = nullptr;
    for(auto it : sets){
        if(it->team->getTeamId() == set2)
            set2ptr = it;
    }
    if(set2ptr == nullptr)
        return StatusType::FAILURE;

    unite(set1ptr, set2ptr);

    return StatusType::SUCCESS;
}

StatusType Union_Find::makeSet(const shared_ptr<Player>& player, const shared_ptr<Team>& team){
    for(auto it : nodes){
        if(it->player == player)
            return StatusType::FAILURE;
    }

    shared_ptr<Node> node(new Node(player, team));
    nodes.push_back(node);

    shared_ptr<Node> occupiedSet = nullptr;
    for(auto it : sets){
        if(it->team->getTeamId() == team->getTeamId()) {
            occupiedSet = it;
            break;
        }
    }

    sets.push_back(node);
    if(occupiedSet != nullptr)
        unite(node, occupiedSet);

    return StatusType::SUCCESS;
}

output_t<shared_ptr<Team>> Union_Find::find(int playerId){

    return StatusType::SUCCESS;
}

void Union_Find::print(){
    cout << "sets:\t";
    for(auto it : sets)
        cout << *((*it).team) << "\t";
    cout << "\n";

    for(int i = 0; i < nodes.size(); ++i){
        shared_ptr<Node> temp = nodes[i];
        while(temp->next != nullptr){
            std::cout << *(temp->player) << "\t->\t";
            temp = temp->next;
        }
        std::cout << *(temp->player) << "\t->\t";

        std::cout << *(temp->team) << "\n";
    }
}












