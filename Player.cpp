//
// Created by Elad on 25/11/2022.
//
#include "Player.h"

using namespace std;

Player::Player(int playerId) : playerId(playerId) {}

Player::Player(int playerId, permutation_t spirit, int ability, int cards, bool goalKeeper):
    playerId(playerId),
    spirit(spirit),
    ability(ability),
    cards(cards),
    goalKeeper(goalKeeper){
}

int Player::getPlayerId() const {
    return playerId;
}

int Player::getCards() const {
    return cards;
}

bool Player::isGoalKeeper() const {
    return goalKeeper;
}

void Player::setCards(int cards_) {
    Player::cards = cards_;
}

const permutation_t Player::getSpirit() const{
    return spirit;
}

int Player::getAbility() const{
    return ability;
}

Player& Player::operator=(const Player& other){
    this->playerId = other.playerId;
    this->ability = other.ability;
    this->cards = other.cards;
    this->goalKeeper = other.goalKeeper;
    this->spirit = other.spirit;

    return *this;
}

std::ostream& operator<<(std::ostream& os, const Player& p){
    return os << "playerId: " << p.playerId;
    /*return os << "playerId: " << p.playerId << ", spirit: " << p.spirit
        << ", ability: " << p.ability << ", cards: " << p.cards << ", goalKeeper: " << p.goalKeeper;*/
}

bool operator==(const Player& p1, const Player& p2){
    return p1.playerId == p2.playerId;
}
