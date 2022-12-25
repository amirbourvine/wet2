#include <algorithm>
#include <iostream>
#include <memory>

#include "Union_Find.h"

using namespace std;

bool arePlayersEqual(const shared_ptr<Node>& p1, const shared_ptr<Node>& p2){
    if(p1 == nullptr || p2 == nullptr)
        return false;
    return p1->player->getPlayerId() == p2->player->getPlayerId();
}
bool areTeamsEqual(const shared_ptr<Node>& t1, const shared_ptr<Node>& t2){
    if(t1 == nullptr|| t2 == nullptr)
        return false;

    if(t1->team == nullptr|| t2->team == nullptr)
        return false;

    return t1->team->getTeamId() == t2->team->getTeamId() &&
        t1->team->isActive() && t2->team->isActive();
}

bool isTeamsGreater(const shared_ptr<Node>& t1, const shared_ptr<Node>& t2){
    if(t1 == nullptr|| t2 == nullptr)
        return false;

    if(t1->team == nullptr|| t2->team == nullptr)
        return false;

    return t1->team->getTeamId() > t2->team->getTeamId() &&
           t1->team->isActive() && t2->team->isActive();
}

bool isEqual_hashobj1(const hash_obj<shared_ptr<Node>>& n1, const hash_obj<shared_ptr<Node>>& n2){
    return arePlayersEqual(n1.val, n2.val);
}

Union_Find::Union_Find():
    nodes(Hash_Table_Chain<shared_ptr<Node>>(arePlayersEqual, isEqual_hashobj1)),
    sets(new RankTree<shared_ptr<Node>>(&isTeamsGreater, &areTeamsEqual))
{}

StatusType Union_Find::unite(shared_ptr<Node>& fromSet, shared_ptr<Node>& toSet){
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
        fromSet->team->setNotActive();
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
    //swap between from and to, in order to keep the hash in the right order
    //this->sets.swap(fromSet, toSet, fromSet->team->getTeamId(), toSet->team->getTeamId());

    fromSet->team->setNotActive();
    fromSet->team = toSet->team;
    toSet->team = nullptr;
    toSet->next = fromSet;

    return StatusType::SUCCESS;
}

StatusType Union_Find::uniteSets(int teamId1, int teamId2){
    if(teamId1 == teamId2)
        return StatusType::FAILURE;

    shared_ptr<Node> demoTeam(new Node(
            make_shared<Player>(-1),
                    make_shared<Team>(teamId1)));

    //output_t<shared_ptr<Node>> out1 = sets.get(demoTeam, teamId1);
    output_t<shared_ptr<Node>*> out1 = sets->find(demoTeam).ans()->getKey();

    if(out1.status() != StatusType::SUCCESS)
        return out1.status();
    shared_ptr<Node> set1 = *out1.ans();

    demoTeam = make_shared<Node>(
            make_shared<Player>(-1),
            make_shared<Team>(teamId2));

    output_t<shared_ptr<Node>*> out2 = sets->find(demoTeam).ans()->getKey();
    if(out2.status() != StatusType::SUCCESS)
        return out2.status();

    shared_ptr<Node> set2 = *out2.ans();

    unite(set2, set1);

    return StatusType::SUCCESS;
}

StatusType Union_Find::makeSet(const shared_ptr<Player>& player, const shared_ptr<Team>& team, int gamesPlayed){
    shared_ptr<Node> demoPlayer = make_shared<Node>(
            player,
            make_shared<Team>(INVALID_TEAM_ID));
    if(nodes.get(demoPlayer, player->getPlayerId()).status() == StatusType::SUCCESS)
        return StatusType::FAILURE;

    shared_ptr<Node> node(new Node(player, team, player->getSpirit(), gamesPlayed));

    nodes.insert(player->getPlayerId(), node);


    shared_ptr<Node> occupiedSet = nullptr;

    shared_ptr<Node> demoTeam(new Node(
            make_shared<Player>(INVALID_PLAYER_ID),
            team));


    output_t<shared_ptr<Node>*> out1 = sets->find(demoTeam).ans()->getKey();
    if(out1.status() == StatusType::SUCCESS) {
        occupiedSet = *out1.ans();
    }

    if(occupiedSet != nullptr) {
        //Fix val games
        node->valgames -= occupiedSet->valgames;

        //Fix permutation track
        //we assume that team spirit was already updated
        node->permutationTrack = occupiedSet->permutationTrack.inv() *
                occupiedSet->team->getSpirit();

        //Fix sets
        node->team = nullptr;
        node->next = occupiedSet;

        return StatusType::SUCCESS;
    }
    else{
        //sets.insert(node->team->getTeamId(), node);
        sets->insert(node);
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

output_t<shared_ptr<Node>> Union_Find::getPlayer(int playerId){
    shared_ptr<Node> demoPlayer = make_shared<Node>(
            make_shared<Player>(playerId),
            make_shared<Team>(INVALID_TEAM_ID));

    output_t<shared_ptr<Node>> out1 = nodes.get(demoPlayer, playerId);
    if(out1.status() != StatusType::SUCCESS)
        return out1.status();

    return out1.ans();
}

output_t<shared_ptr<Team>> Union_Find::find(int playerId){
    //Find player in array
    shared_ptr<Node> demoPlayer = make_shared<Node>(
            make_shared<Player>(playerId),
            make_shared<Team>(INVALID_TEAM_ID));

    output_t<shared_ptr<Node>> out1 = nodes.get(demoPlayer, playerId);
    if(out1.status() != StatusType::SUCCESS)
        return out1.status();
    shared_ptr<Node> player = out1.ans();

    return findaux(player);
}

output_t<int> Union_Find::calcGamesPlayed(int playerId){
    //Find player in array
    shared_ptr<Node> demoPlayer = make_shared<Node>(
            make_shared<Player>(playerId),
            make_shared<Team>(INVALID_TEAM_ID));

    output_t<shared_ptr<Node>> out1 = nodes.get(demoPlayer, playerId);
    if(out1.status() != StatusType::SUCCESS)
        return out1.status();
    shared_ptr<Node> player = out1.ans();

    //Calc games played
    int gamesPlayed = 0;
    shared_ptr<Node> node = player;
    shared_ptr<Node> keep;

    while(node != nullptr) {
        gamesPlayed += node->valgames;
        keep = node;
        node = node->next;
    }

    gamesPlayed += keep->team->getGamesPlayedAsTeam();
    findaux(player);

    return gamesPlayed;
}

output_t<permutation_t> Union_Find::calcPartialPermutation(int playerId){
    //Find player in array
    shared_ptr<Node> demoPlayer = make_shared<Node>(
            make_shared<Player>(playerId),
            make_shared<Team>(INVALID_TEAM_ID));

    output_t<shared_ptr<Node>> out1 = nodes.get(demoPlayer, playerId);
    if(out1.status() != StatusType::SUCCESS)
        return out1.status();
    shared_ptr<Node> player = out1.ans();

    //Calc partial permutation
    permutation_t partialPermutation = permutation_t::neutral();
    shared_ptr<Node> node = player;
    while(node != nullptr) {
        partialPermutation = node->permutationTrack * partialPermutation;
        node = node->next;
    }

    findaux(player);

    return partialPermutation;
}

void Union_Find::print(){
    /*hash_obj<shared_ptr<Node>>** setsArr(sets.returnNarrowedArray());
    for(int i = 0; i < sets.getObjNum(); ++i) {
        if(setsArr[i]->val->team != nullptr)
            cout << *(setsArr[i]->val->team) << "\t";
    }
    cout << "\n";*/
    //sets->print2D();

    hash_obj<shared_ptr<Node>>** nodesArr(nodes.returnNarrowedArray());
    for(int i = 0; i < nodes.getObjNum(); ++i){
        shared_ptr<Node> temp = nodesArr[i]->val;
        while(temp->next != nullptr){
            std::cout << *(temp->player) << "\t->\t";
            //std::cout << *(temp->player) << ", valgames: " << temp->valgames
            //  << ", permutation: " << temp->permutationTrack << "\t->\t";
            temp = temp->next;
        }
        std::cout << *(temp->player) << "\t->\t";
        //std::cout << *(temp->player) << ", valgames: " << temp->valgames
        //<< ", permutation: " << temp->permutationTrack << "\t->\t";

        std::cout << *(temp->team) << "\n";
    }

    delete[] nodesArr;
}

