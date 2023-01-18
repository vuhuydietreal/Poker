//by vuhuydiet
#pragma once
#include<string>
#include<map>
//"\xe2\x99\xa3"
//"\xe2\x99\xa5"
//"\xe2\x99\xa0"
//"\xe2\x99\xa6"

string clubs = "\u2663";
string diamonds = "\u2666";
string hearts = "\u2665";
string spades = "\u2660";
char heart = 35;
char spade = 36;
char diamond = 37;
char club = 38;

class Card {
public:
    int num;
    int type;

    map<int, char> num_map = {{0, '2'}, {1, '3'}, {2, '4'}, {3, '5'}, {4, '6'},
                              {5, '7'}, {6, '8'}, {7, '9'}, {8, 'T'}, {9, 'J'},
                              {10, 'Q'}, {11, 'K'}, {12, 'A'}};

public:
    Card() {}
    Card(int n, int t) : num(n), type(t) {}

    void display() {
        cout << num_map[num];
        if (type==0) cout << "$" << " ";
        if (type==1) cout << "&" << " ";
        if (type==2) cout << "?" << " ";
        if (type==3) cout << "%" << " ";
    }
    
    static Card to_card(int x) {
        int n = x%13;
        int t = x/13;

        return Card(n, t);
    }

    void swap(Card& a, Card& b) {
        Card temp = a; a = b; b = temp;
    }
};