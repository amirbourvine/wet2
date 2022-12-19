//
// Created by Elad on 25/11/2022.
//

#ifndef DS_WET1_TEAM_H
#define DS_WET1_TEAM_H

#include <memory>
#include "Player.h"

using namespace std;

const static int INVALID_TEAM_ID = -1;

class Team {
private:
    int teamId;
    int points;
    int playersCount;
    int goalKeepersAmount;
    int ability;
    bool active;
    int gamesPlayedAsTeam;
    permutation_t spirit;

public:

    explicit Team(int teamId);
    Team(Team& other) = delete;
    Team& operator=(const Team& other) = delete;
    ~Team() = default;

    friend std::ostream& operator<<(std::ostream&, const Team&);

    int getTeamId() const;
    int getPoints() const;
    void addPoints(int points);
    int getGoalKeepersAmount() const;
    void setGoalKeepersAmount(int goalKeepersAmount);
    int getGamesPlayedAsTeam() const;
    void setGamesPlayedAsTeam(int gamesPlayedAsTeam);
    int getPlayersCount() const;
    void addToPlayersCount(int amount);

    int getAbility() const;
    void incAbility(int playerAbility);
    bool isActive() const;
    void setNotActive();
    permutation_t getSpirit() const;
    void addToSpirit(permutation_t permutation);

    StatusType add_player(const shared_ptr<Player>& p);
};

#endif //DS_WET1_TEAM_H
