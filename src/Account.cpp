//by vuhuydiet
#pragma once
#include<string>

class Account {
public:
    string userName;
    int money;

public:
    Account() : userName("unknown"), money(0) {}
    Account(string name, int money) : userName(name), money(money) {}
    Account(const Account& i) : userName(i.userName), money(i.money) {}

    void display() {
        cout << "Name: " << userName << "\n";
        cout << "Money: $" << money << "\n";
    }

    void setMoney(int money) {
        this->money += money;
    }
};