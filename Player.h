//
// Created by Elad on 25/11/2022.
//

#ifndef DS_WET1_PLAYER_H
#define DS_WET1_PLAYER_H
#include <memory>
#include <iostream>

#include "wet2util.h"


class Team;

using namespace std;

const static int INVALID_PLAYER_ID = -1;


class Player {
private:
    int playerId;
    permutation_t spirit;
    int ability;
    int cards;
    bool goalKeeper;

public:
    explicit Player(int playerId);
    explicit Player(int playerId, const permutation_t& spirit, int ability, int cards, bool goalKeeper);
    Player(Player& other) = default;
    Player& operator=(const Player& other);
    ~Player() = default;

    friend std::ostream& operator<<(std::ostream&, const Player&);
    friend bool operator==(const Player&, const Player&);

    void setCards(int cards);

    int getPlayerId() const;
    const permutation_t getSpirit() const;
    int getAbility() const;
    int getCards() const;
    bool isGoalKeeper() const;
};


#endif //DS_WET1_PLAYER_H
