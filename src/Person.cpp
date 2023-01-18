//by vuhuydiet
#pragma once
#include<vector>
#include<algorithm>
#include<iostream>
#include "Hand.cpp"
#include "Point.cpp"
#include "TableCards.cpp"
#include "Player.cpp"
using namespace std;

class Person : public Player {
public:
    Person() {}
    Person(const Account& a) : Player(a) {}
    ~Person() {}

    int bet(TableCards table, int pot, int roundBet) {
        int amount = 0;
        bool valid = true;
        do {
            display(table, pot, roundBet);
            if(!valid) cout << "Your bet must not be greater than your money!\n";
            valid = true;
            cout << "Enter your choice: 1. Check   2. Bet: 2\n";
            cout << "Enter your bet: ";
            cin >> amount;
            if (amount>money) valid = false;
        } while(amount<=0 || amount>money);

        setMoney(-amount);
        curBet = amount;
        return amount;
    }
    int call(int roundBet) {
        int add = roundBet - curBet;
        curBet = roundBet;

        setMoney(-add);
        return add;
    }
    int raise(TableCards table, int pot, int roundBet) {
        int amount;
        bool valid = true;
        do {
            display(table, pot, roundBet);
            if (!valid) cout << "Your bet must not be greater than your money!\n";
            cout << "Enter your choice: 1. Call   2. Raise   3. Fold: 2\n";
            cout << "Enter your bet: ";
            cin >> amount;
        } while(amount<=0 || amount>money);

        amount += roundBet - curBet;
        setMoney(-amount);
        curBet += amount;
        return amount;
    }
    int fold() {
        return -1;
    }
    int allIn() {
        int add = money;
        money = 0;
        curBet = add;

        return add;
    }
    void display(TableCards table, int pot, int roundBet) {
        system("cls");

        Account::display();

        cout << "\nHand: ";
        hand.display(); cout << "\n";
        cout << "Table: ";
        table.display(); cout << "\n";

        cout << "\nPot Size: $" << pot << "\n";
        cout << "\nRound Bet: $" << roundBet << "\n";
        cout << "Current Bet: $" << curBet << "\n";
        cout << "To Call: $" << roundBet - curBet << "\n\n";
    }
    int action(TableCards table, int pot, int roundBet) {
        if (money==0) return 0;

        char act;
        bool boo = true;
        do {
            display(table, pot, roundBet);
            if (!boo) cout << "Invalid choice!!!\n";

            boo = true;

            if (roundBet==0) {
                cout << "Enter your choice: 1. Check   2. Bet   3. All in: ";
                cin >> act;
                if (act<'1' || act>'3') boo = false;

                if (act=='1') return 0;
                if (act=='2') return bet(table, pot, roundBet);
                if (act=='3') return allIn();
            }
            else {
                cout << "Enter your choice: 1. Call   2. Raise   3. Fold   4. All in: ";
                cin >> act;
                if (act<'1' || act>'4') boo = false;

                if (act=='1') return call(roundBet);
                if (act=='2') return raise(table, pot, roundBet);
                if (act=='3') return fold();
                if (act=='4') return allIn();
            }
        } while(!boo);
    }
};