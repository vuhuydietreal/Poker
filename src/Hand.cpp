//by vuhuydiet
#pragma once
#include "Card.cpp"
using namespace std;

class Hand {
public:
    Card first;
    Card second;

public:
    Hand() {}
    Hand(Card first, Card second) : first(first), second(second) {}

    void display() {
        first.display();
        second.display();
    }
};
