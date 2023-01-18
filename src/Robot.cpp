//by vuhuydiet
#pragma once
#include<vector>
#include<algorithm>
#include<iostream>
#include "Hand.cpp"
#include "Point.cpp"
#include "Account.cpp"
#include "TableCards.cpp"
#include "Player.cpp"
using namespace std;

class Robot : public Player {
public:
    Robot() {}
    Robot(const Account& a) : Player(a) {}
    ~Robot() {}

    int action(TableCards table, int pot, int roundBet) {
        if (roundBet==0) return 0;
        if (roundBet>0) {
            int add = roundBet - curBet;
            curBet = roundBet;
            setMoney(-add);

            return add;
        }
    }
};