//
// Created by amirb on 22/12/2022.
//

#include <iostream>

#include "Union_Find.h"

int main(){
    Union_Find uf;

    int a[5] = {1, 2, 3, 4, 0};
    permutation_t per1(a);

    shared_ptr<Team> t1(new Team(1));
    t1->setGamesPlayedAsTeam(2);
    shared_ptr<Player> p1(new Player (1, per1, 0, 0, false));
    shared_ptr<Player> p2(new Player(2, per1, 0, 0, false));

    shared_ptr<Team> t2(new Team(2));
    t2->setGamesPlayedAsTeam(2);
    shared_ptr<Team> t3(new Team(3));
    t3->setGamesPlayedAsTeam(2);
    shared_ptr<Player> p3(new Player (3, per1, 0, 0, false));
    shared_ptr<Team> t4(new Team(4));
    t4->setGamesPlayedAsTeam(3);
    shared_ptr<Player> p4(new Player (4, per1, 0, 0, false));
    shared_ptr<Player> p5(new Player (5, per1, 0, 0, false));

    t1->add_player(p1);
    uf.makeSet(p1, t1, 1);

    t2->add_player(p2);
    uf.makeSet(p2, t2, 3);

    t3->add_player(p3);
    uf.makeSet(p3, t3, 9);

    t4->add_player(p4);
    uf.makeSet(p4, t4, 17);
    t4->add_player(p5);
    uf.makeSet(p5, t4, 17);

    cout<<"****************************************"<<endl;
    uf.printHashTeams();
    cout<<"****************************************"<<endl;
    uf.print();

    StatusType st;

    uf.uniteSets(2, 1);
    t2->addToSpirit(t1->getSpirit());
    t2->addToPlayersCount(t1->getPlayersCount());

    cout<<"****************************************"<<endl;
    uf.printHashTeams();
    cout<<"****************************************"<<endl;
    uf.print();

    uf.uniteSets(3, 2);
    t3->addToSpirit(t2->getSpirit());
    t3->addToPlayersCount(t2->getPlayersCount());

    cout<<"****************************************"<<endl;
    uf.printHashTeams();
    cout<<"****************************************"<<endl;
    uf.print();

    st = uf.uniteSets(4, 3);
    t4->addToSpirit(t3->getSpirit());
    t4->addToPlayersCount(t3->getPlayersCount());

    cout<<"****************************************"<<endl;
    uf.printHashTeams();
    cout<<"****************************************"<<endl;
    uf.print();

//    cout << uf.calcPartialPermutation(5).ans() << "\n";
//
//    uf.print();
//
//    cout << uf.calcPartialPermutation(5).ans() << "\n";

    return 0;
}