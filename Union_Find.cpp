#include <algorithm>
#include <iostream>
#include <memory>

#include "Union_Find.h"

StatusType Union_Find::unite(const shared_ptr<Node>& fromSet, const shared_ptr<Node>& toSet){
    if(fromSet->team == nullptr || toSet->team == nullptr)
        return StatusType::FAILURE;

    if(fromSet->team->getTeamId() == toSet->team->getTeamId()){
        return StatusType::FAILURE;
    }

    if(fromSet->team->getPlayersCount() <= toSet->team->getPlayersCount()){
        //Fix val games
        toSet->valgames = toSet->valgames + toSet->team->getGamesPlayedAsTeam();
        toSet->team->setGamesPlayedAsTeam(0);
        fromSet->valgames = fromSet->valgames + fromSet->team->getGamesPlayedAsTeam() - toSet->valgames;

        //Fix permutation track
        fromSet->permutationTrack = toSet->permutationTrack.inv() *
                toSet->team->getSpirit() * fromSet->permutationTrack;

        //Fix sets
        sets.erase(std::find(sets.begin(), sets.end(), fromSet));
        fromSet->team = nullptr;
        fromSet->next = toSet;

        return StatusType::SUCCESS;
    }

    //Fix val games
    fromSet->valgames = fromSet->valgames + fromSet->team->getGamesPlayedAsTeam();
    toSet->valgames = toSet->valgames + toSet->team->getGamesPlayedAsTeam() - fromSet->valgames;
    toSet->team->setGamesPlayedAsTeam(0);

    //Fix Permutation track
    fromSet->permutationTrack = toSet->team->getSpirit() * fromSet->permutationTrack;
    toSet->permutationTrack = fromSet->permutationTrack.inv() * toSet->permutationTrack;

    //Fix sets
    sets.erase(std::find(sets.begin(), sets.end(), toSet));
    fromSet->team = toSet->team;
    toSet->team = nullptr;
    toSet->next = fromSet;

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

StatusType Union_Find::makeSet(const shared_ptr<Player>& player, const shared_ptr<Team>& team, int gamesPlayed){
    for(auto it : nodes){
        if(it->player == player)
            return StatusType::FAILURE;
    }

    shared_ptr<Node> node(new Node(player, team, player->getSpirit(), gamesPlayed));
    nodes.push_back(node);

    shared_ptr<Node> occupiedSet = nullptr;
    for(auto it : sets){
        if(it->team->getTeamId() == team->getTeamId()) {
            occupiedSet = it;
            break;
        }
    }

    sets.push_back(node);
    if(occupiedSet != nullptr) {
        node->valgames += node->team->getGamesPlayedAsTeam();
        node->team = std::make_shared<Team>(INVALID_TEAM_ID);
        if(unite(node, occupiedSet) != StatusType::SUCCESS)
            return unite(node, occupiedSet);
    }

    return StatusType::SUCCESS;
}

shared_ptr<Team> Union_Find::findaux(shared_ptr<Node>& start){
    //find player's team
    shared_ptr<Node> set = start;
    permutation_t totalPermutationTrack = permutation_t::neutral();
    int sum = 0;
    while(set->next != nullptr){
        sum += set->valgames;
        totalPermutationTrack = set->permutationTrack * totalPermutationTrack;
        set = set->next;
    }

    //Fix the set
    shared_ptr<Node> temp;
    int valgamesFix = 0;
    permutation_t permutationTrackFix = permutation_t::neutral();
    while(start->next != nullptr){
        //Fix val games
        int preValGames = start->valgames;
        start->valgames = sum - valgamesFix;
        valgamesFix += preValGames;

        //Fix permutation track
        permutation_t prePermutationTrack = start->permutationTrack;
        start->permutationTrack = permutationTrackFix.inv() * totalPermutationTrack;
        permutationTrackFix = prePermutationTrack * permutationTrackFix;

        //Connect directly to set
        temp = start->next;
        start->next = set;
        start = temp;
    }

    return set->team;
}
output_t<shared_ptr<Team>> Union_Find::find(int playerId){
    //Find player in array
    shared_ptr<Node> player = nullptr;
    for(auto it : nodes){
        if(it->player->getPlayerId() == playerId)
            player = it;
    }
    if(player == nullptr)
        return StatusType::FAILURE;

    return findaux(player);
}

output_t<int> Union_Find::calcGamesPlayed(int playerId){
    //Find player in array
    shared_ptr<Node> player = nullptr;
    for(auto it : nodes){
        if(it->player->getPlayerId() == playerId)
            player = it;
    }
    if(player == nullptr)
        return StatusType::FAILURE;

    //Calc games played
    int gamesPlayed = 0;
    shared_ptr<Node> node = player;
    while(node != nullptr) {
        gamesPlayed += node->valgames;
        node = node->next;
    }

    findaux(player);

    return gamesPlayed;
}

output_t<permutation_t> Union_Find::calcPartialPermutation(int playerId){
    //Find player in array
    shared_ptr<Node> player = nullptr;
    for(auto it : nodes){
        if(it->player->getPlayerId() == playerId)
            player = it;
    }
    if(player == nullptr)
        return StatusType::FAILURE;

    //Calc partial permutation
    permutation_t partialPermutation = permutation_t::neutral();
    shared_ptr<Node> node = player;
    while(node != nullptr) {
        partialPermutation = node->permutationTrack * partialPermutation;
        node = node->next;
    }

    //findaux(player);

    return partialPermutation;
}

void Union_Find::print(){
    cout << "sets:\t";
    for(auto it : sets)
        cout << *((*it).team) << "\t";
    cout << "\n";

    for(int i = 0; i < nodes.size(); ++i){
        shared_ptr<Node> temp = nodes[i];
        while(temp->next != nullptr){
            std::cout << *(temp->player) << ", valgames: " << temp->valgames
                << ", permutation: " << temp->permutationTrack << "\t->\t";
            temp = temp->next;
        }
        std::cout << *(temp->player) << ", valgames: " << temp->valgames
        << ", permutation: " << temp->permutationTrack << "\t->\t";

        std::cout << *(temp->team) << "\n";
    }
}












