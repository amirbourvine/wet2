//
// Created by Elad on 25/11/2022.
//
#include <exception>
#include <memory>
#include "Team.h"

using namespace std;

Team::Team(int teamId) :
        teamId(teamId),
        points(0),
        playersCount(0),
        goalKeepersAmount(0),
        ability(0),
        active(true),
        gamesPlayedAsTeam(0),
        spirit(permutation_t::neutral())
{}

std::ostream& operator<<(std::ostream& os, const Team& t){
    return os << "TeamId: " << t.teamId;
    /*return os << "TeamId: " << t.teamId << ", points: " << t.points
        << ", playersCount: " << t.playersCount << ", GoalKeepersAmount: " << t.goalKeepersAmount
        << ", ability: " << t.ability << ", active: " << t.active
        << ", gamesPlayedAsTeam: " << t.gamesPlayedAsTeam;*/
}

int Team::getTeamId() const {
    return teamId;
}

int Team::getPoints() const {
    return points;
}

void Team::addPoints(int points){
    this->points += points;
}

int Team::getGoalKeepersAmount() const{
    return goalKeepersAmount;
}

void Team::setGoalKeepersAmount(int goalKeepersAmount){
    this->goalKeepersAmount = goalKeepersAmount;
}

int Team::getGamesPlayedAsTeam() const {
    return gamesPlayedAsTeam;
}

void Team::setGamesPlayedAsTeam(int gamesPlayedAsTeam) {
    Team::gamesPlayedAsTeam = gamesPlayedAsTeam;
}

int Team::getPlayersCount() const {
    return playersCount;
}

void Team::addToPlayersCount(int amount){
    playersCount += amount;
}



int Team::getAbility() const{
    return this->ability;
}

void Team::incAbility(int playerAbility){
    ability += playerAbility;
}

bool Team::isActive() const{
    return active;
}

void Team::setActive(bool active){
    this->active = active;
}

permutation_t Team::getSpirit() const{
    return spirit;
}

void Team::addToSpirit(permutation_t permutation){
    this->spirit = this->spirit * permutation;
}

StatusType Team::add_player(const shared_ptr<Player>& p) {
    goalKeepersAmount += p->isGoalKeeper();
    ability += p->getAbility();

    ++playersCount;

    spirit = spirit * p->getSpirit();

    return StatusType::SUCCESS;
}





