#include "worldcup23a2.h"

bool are_teams_equal_id(const shared_ptr<Team>& team1, const shared_ptr<Team>& team2){
    return team1->getTeamId()==team2->getTeamId();
}

bool is_larger_teams_id(const shared_ptr<Team>& team1, const shared_ptr<Team>& team2){
    return team1->getTeamId()>team2->getTeamId();
}

bool are_teams_equal_ability(const shared_ptr<Team>& team1, const shared_ptr<Team>& team2){
    //includes only active teams
    return team1->getTeamId()==team2->getTeamId();
}

bool is_larger_teams_ability(const shared_ptr<Team>& team1, const shared_ptr<Team>& team2){
    if(team1->getAbility()>team2->getAbility())
        return true;
    if(team1->getAbility()<team2->getAbility())
        return false;
    return team1->getTeamId()>team2->getTeamId();
}

world_cup_t::world_cup_t():
    teams_id(new RankTree<shared_ptr<Team>>(&is_larger_teams_id, &are_teams_equal_id)),
    teams_ability(new RankTree<shared_ptr<Team>>(&is_larger_teams_ability, &are_teams_equal_ability)),
    uf(new Union_Find()), active_teams(0)
{
}

world_cup_t::~world_cup_t()
{
}

StatusType world_cup_t::add_team(int teamId)
{
    StatusType st;
	shared_ptr<Team> new_team(new Team(teamId));
    st = this->teams_id->insert(new_team);
    if(st!=StatusType::SUCCESS){
        return st;
    }
    st = this->teams_ability->insert(new_team);
    if(st!=StatusType::SUCCESS){
        return st;
    }
    this->active_teams++;
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
    StatusType st;
    shared_ptr<Team> temp(new Team(teamId));//will be deleted automatically
    output_t<RankNode<std::shared_ptr<Team>>*> output = this->teams_id->find(temp);
    if(output.status()!=StatusType::SUCCESS){
        return output.status();
    }
    shared_ptr<Team> team = *(output.ans()->getKey().ans());

    st = this->teams_id->remove(team);
    if(st!=StatusType::SUCCESS){
        return st;
    }

    st = this->teams_ability->remove(team);
    if(st!=StatusType::SUCCESS){
        return st;
    }

    this->active_teams--;

    team->setNotActive();

    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
    StatusType st;

	shared_ptr<Player> player(new Player(playerId, spirit, ability, cards, goalKeeper));

    shared_ptr<Team> temp(new Team(teamId));//will be deleted automatically
    output_t<RankNode<std::shared_ptr<Team>>*> output = this->teams_id->find(temp);
    if(output.status()!=StatusType::SUCCESS){
        return output.status();
    }

    shared_ptr<Team> team = *(output.ans()->getKey().ans());

    st = this->teams_ability->remove(team);
    if(st!=StatusType::SUCCESS){
        return st;
    }

    team->add_player(player);

    this->uf->makeSet(player, team, gamesPlayed);

    st = this->teams_ability->insert(team);
    if(st!=StatusType::SUCCESS){
        return st;
    }

	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
    if(teamId1<=0 || teamId2<=0 || teamId1==teamId2){
        return StatusType::INVALID_INPUT;
    }

    shared_ptr<Team> temp1(new Team(teamId1));//will be deleted automatically
    output_t<RankNode<std::shared_ptr<Team>>*> output1 = this->teams_id->find(temp1);
    if(output1.status()!=StatusType::SUCCESS){
        return output1.status();
    }
    shared_ptr<Team> team1 = *(output1.ans()->getKey().ans());

    shared_ptr<Team> temp2(new Team(teamId2));//will be deleted automatically
    output_t<RankNode<std::shared_ptr<Team>>*> output2 = this->teams_id->find(temp2);
    if(output2.status()!=StatusType::SUCCESS){
        return output2.status();
    }
    shared_ptr<Team> team2 = *(output2.ans()->getKey().ans());

    if(team1->getGoalKeepersAmount()<1 || team2->getGoalKeepersAmount()<1)
        return StatusType::FAILURE;

    int power1 = team1->getAbility() + team1->getPoints();
    int power2 = team2->getAbility() + team2->getPoints();

    if(power1>power2){
        team1->addPoints(3);
    }
    if(power1<power2){
        team2->addPoints(3);
    }
    if(power1==power2){
        int strength1 = team1->getSpirit().strength();
        int strength2 = team2->getSpirit().strength();
        if(strength1>strength2){
            team1->addPoints(3);
        }
        if(strength1<strength2){
            team2->addPoints(3);
        }
        if(strength1==strength2){
            team1->addPoints(1);
            team2->addPoints(1);
        }
    }

    team1->setGamesPlayedAsTeam(team1->getGamesPlayedAsTeam()+1);
    team2->setGamesPlayedAsTeam(team2->getGamesPlayedAsTeam()+1);
    return 0;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
	// TODO: Your code goes here
	return 22;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
	return 30003;
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	// TODO: Your code goes here
	return 12345;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	// TODO: Your code goes here
	return permutation_t();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}
