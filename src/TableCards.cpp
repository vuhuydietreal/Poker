//by vuhuydiet
#pragma once
#include<map>
#include "Card.cpp"
using namespace std;

class TableCards {
public:
    vector<Card> table;
    int num_of_cards;

public:
    TableCards() : num_of_cards(0) {}

    void display() {
        for(Card c : table) {
            c.display();
        }
    }

    void flop(Card a, Card b, Card c) {
        table.push_back(a);
        table.push_back(b);
        table.push_back(c);
        num_of_cards += 3;
    }

    void turn(Card a) {
        table.push_back(a);
        num_of_cards++;
    }

    void river(Card a) {
        table.push_back(a);
        num_of_cards++;
    }
};