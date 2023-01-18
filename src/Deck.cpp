//by vuhuydiet
#pragma once
#include<vector>
#include<chrono>
#include<algorithm>
#include<random>
#include "Card.cpp"

class Deck {
private:
    vector<int> deck;
    vector<int>::iterator pt;

public:
    Deck() {}
    Deck(bool construct) {
        for(int i=0; i<52; i++) {
            deck.push_back(i);
        }
        pt = deck.begin();
        shuffle_cards();
    }

    void shuffle_cards() {
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(pt, deck.end(), default_random_engine(seed));
    }

    Card draw() {
        Card c = Card::to_card(*pt);
        pt++;
        return c;
    }
};