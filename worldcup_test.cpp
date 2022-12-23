//
// Created by amirb on 22/12/2022.
//

#include "worldcup23a2.h"

int main(){
    auto* obj = new world_cup_t();
    StatusType st;
    int a[5] = {1, 2, 3, 4, 0};
    permutation_t per1(a);

    obj->add_team(1);
    obj->add_team(20);
    obj->add_team(87);

    obj->add_player(1, 1, permutation_t::neutral(), 5, 10, 3, true);
    obj->add_player(2, 1, per1, 3, 2, 1, false);
    obj->add_player(3, 1, per1, 6, 3, 2, true);
    obj->add_player(4, 1, per1, 65, 50, 20, false);

    cout<<"***************************ADD_CARDS AND GET_CARDS*****************************"<<endl;

    output_t<int> output = obj->get_player_cards(4);
    if(output.status()==StatusType::SUCCESS)
        cout<<output.ans()<<endl;
    else
        cout<<"FAILURE"<<endl;

    obj->add_player_cards(4, 4);

    output_t<int> output1 = obj->get_player_cards(4);
    if(output1.status()==StatusType::SUCCESS)
        cout<<output1.ans()<<endl;
    else
        cout<<"FAILURE"<<endl;

    output_t<int> output2 = obj->get_player_cards(8);
    if(output2.status()==StatusType::SUCCESS)
        cout<<output2.ans()<<endl;
    else
        cout<<"FAILURE"<<endl;

    cout<<"***************************num_played_games_for_player*****************************"<<endl;
    output_t<int> output3 = obj->num_played_games_for_player(1);
    if(output3.status()==StatusType::SUCCESS)
        cout<<output3.ans()<<endl;
    else
        cout<<"FAILURE"<<endl;


    cout<<"***************************REMOVE_TEAM*****************************"<<endl;
    obj->add_player(21, 20, permutation_t::neutral(), 0, 12, 6, true);
    obj->add_player(22, 20, per1, 60, 32, 30, true);
    obj->add_player(23, 20, permutation_t::neutral(), 6, 3, 2, true);
    obj->add_player(24, 20, per1, 68, 26, 10, false);

    obj->remove_team(20);

    cout<<"***************************ADD_TEAM THAT WAS REMOVED *****************************"<<endl;
    obj->add_team(20);
    obj->add_player(25, 20, permutation_t::neutral(), 0, 12, 6, true);
    obj->add_player(26, 20, per1, 60, 32, 30, true);
    obj->add_player(27, 20, permutation_t::neutral(), 6, 3, 2, true);
    obj->add_player(28, 20, per1, 68, 26, 10, false);


    cout<<"***************************OVERALL STATUS   *****************************"<<endl;
    cout<<"*****************ID*******************"<<endl;
    obj->printTeams_id();
    cout<<"*****************ABILITY*******************"<<endl;
    obj->printTeams_ability();
    cout<<"*****************UF  *******************"<<endl;
    obj->print_uf();

    cout<<"***************************get_ith_pointless_ability*****************************"<<endl;
    output_t<int> output4 = obj->get_ith_pointless_ability(1);
    if(output4.status()==StatusType::SUCCESS)
        cout<<output4.ans()<<endl;
    else
        cout<<"FAILURE"<<endl;

    cout<<endl;
    cout<<"***************************get_partial_spirit*****************************"<<endl;
    output_t<permutation_t> output5 = obj->get_partial_spirit(4);
    if(output5.status()==StatusType::SUCCESS)
        cout<<output5.ans()<<endl;
    else
        cout<<"FAILURE"<<endl;


    cout<<"***************************play_match*****************************"<<endl;
    obj->play_match(1,20);

    output_t<int> output6 = obj->get_team_points(1);
    if(output6.status()==StatusType::SUCCESS)
        cout<<output6.ans()<<endl;
    else
        cout<<"FAILURE"<<endl;

    output_t<int> output7 = obj->get_team_points(20);
    if(output7.status()==StatusType::SUCCESS)
        cout<<output7.ans()<<endl;
    else
        cout<<"FAILURE"<<endl;

    output_t<int> output8 = obj->num_played_games_for_player(4);
    if(output8.status()==StatusType::SUCCESS)
        cout<<output8.ans()<<endl;
    else
        cout<<"FAILURE"<<endl;


    cout<<"***************************OVERALL STATUS   *****************************"<<endl;
    cout<<"*****************ID*******************"<<endl;
    obj->printTeams_id();
    cout<<"*****************ABILITY*******************"<<endl;
    obj->printTeams_ability();
    cout<<"*****************UF  *******************"<<endl;
    obj->print_uf();

    cout<<"***************************buy_team*****************************"<<endl;
    obj->buy_team(1,20);

    cout<<"***************************OVERALL STATUS   *****************************"<<endl;
    cout<<"*****************ID*******************"<<endl;
    obj->printTeams_id();
    cout<<"*****************ABILITY*******************"<<endl;
    obj->printTeams_ability();
    cout<<"*****************UF  *******************"<<endl;
    obj->print_uf();


    cout<<"***************************ADD_CARDS AND GET_CARDS*****************************"<<endl;

    output_t<int> output10 = obj->get_player_cards(4);
    if(output10.status()==StatusType::SUCCESS)
        cout<<output10.ans()<<endl;
    else
        cout<<"FAILURE"<<endl;

    obj->add_player_cards(4, 4);

    output_t<int> output11 = obj->get_player_cards(4);
    if(output11.status()==StatusType::SUCCESS)
        cout<<output11.ans()<<endl;
    else
        cout<<"FAILURE"<<endl;

    cout<<"***************************num_played_games_for_player*****************************"<<endl;
    output_t<int> output13 = obj->num_played_games_for_player(1);
    if(output13.status()==StatusType::SUCCESS)
        cout<<output13.ans()<<endl;
    else
        cout<<"FAILURE"<<endl;

    cout<<"***************************get_ith_pointless_ability*****************************"<<endl;
    output_t<int> output14 = obj->get_ith_pointless_ability(1);
    if(output14.status()==StatusType::SUCCESS)
        cout<<output14.ans()<<endl;
    else
        cout<<"FAILURE"<<endl;

    cout<<"***************************get_partial_spirit*****************************"<<endl;
    output_t<permutation_t> output15 = obj->get_partial_spirit(28);
    if(output15.status()==StatusType::SUCCESS)
        cout<<output15.ans()<<endl;
    else
        cout<<"FAILURE"<<endl;

    return 0;
}
