//by vuhuydiet
#pragma once
#include<vector>
#include<algorithm>
#include<iostream>
#include "Hand.cpp"
#include "Point.cpp"
#include "TableCards.cpp"
#include "Account.cpp"
using namespace std;

class Player : public Account {
public:
    Hand hand;
    vector<Card> cards;

    Point point;


public:
    int curBet;

    Player() {}
    Player(const Account& a) : Account(a) {}
    virtual ~Player() {}

    //Infomation
    void newGame() {
        hand = Hand(Card(0, 0), Card(0, 0));
        cards.clear();
        point = Point(0, 0, 0);
    }

    virtual int action(TableCards table, int pot, int roundBet) {
        return 0;
    }


    void pre_flop(Card a, Card b) {
        hand = Hand(a, b);
        cards.push_back(a);
        cards.push_back(b);
        hand.display();
    }
    void flop(Card a, Card b, Card c) {
        cards.push_back(a);
        cards.push_back(b);
        cards.push_back(c);
        get_best_comb();
    }
    void turn(Card a) {
        cards.push_back(a);
        get_best_comb();
    }
    void river(Card a) {
        cards.push_back(a);
        get_best_comb();
    }

    //Point System
    Point getPoint() {
        return point;
    }
    string getStatus() {
        return point.getStatus();
    }

    void get_best_comb() {
        point.clear();


        //-----------Check Num--------------//
        sort(cards.begin(), cards.end(), 
            [](Card a, Card b) -> bool {
                return a.num < b.num;
            }
        );


        vector<int> pairs; pairs.clear();
        vector<int> triples; triples.clear();
        int quad = -1;
        int ace_s = cards[0].num;

        int cnt = 1;
        int longest_straight = 0;
        int cnt_s = 1;
        for(int i=1; i<cards.size(); i++) {
            if (cards[i].num==cards[i-1].num) {
                cnt++;
                if (cnt==2) {
                    pairs.push_back(cards[i].num);
                }
                if (cnt==3) {
                    pairs.pop_back();
                    triples.push_back(cards[i].num);
                }
                if (cnt==4) {
                    triples.pop_back();
                    quad = cards[i].num;
                }
            }
            else {
                cnt = 1;
                if (cards[i].num==cards[i-1].num+1) {
                    cnt_s++;
                    if (cnt_s<longest_straight) continue;
                    ace_s = cards[i].num;
                    longest_straight = cnt_s;
                } 
                else {
                    cnt_s = 1;
                }
            }
        }
        
        //High Card
        int x = 0;
        for(int i=cards.size()-1; i>cards.size()-6; i--) {
            x += 1<<cards[i].num;
        }
        point.setPoint(0, x, 0);


        //Pair
        if (pairs.size()==1) {
            int p = *pairs.begin();
            vector<int> temp;
            for(int i=cards.size()-1; i>=0; i--) {
                if (temp.size()==3) break;
                if (cards[i].num==p) continue;

                temp.push_back(cards[i].num);
            }
            point.setPoint(1, p, (1<<temp[0]) + (1<<temp[1]) + (1<<temp[2]));
        }

        //TwoPair
        if (pairs.size()>=2) {
            int p1 = pairs[pairs.size()-1];
            int p2 = pairs[pairs.size()-2];
            int p3 = 0;
            for(int i=cards.size()-1; i>=0; i--) {
                if (cards[i].num==p1 || cards[i].num==p2) continue;

                p3 = cards[i].num;
                break;
            }
            point.setPoint(2, (1<<p1)+(1<<p2), p3);
        }

        //Triple
        if (triples.size()==1 && pairs.size()==0) {
            int trp = *triples.begin();
            vector<int> temp;
            for(int i=cards.size()-1; i>=0; i--) {
                if (temp.size()==2) break;;
                if (cards[i].num==trp) continue;

                temp.push_back(cards[i].num);
            }
            point.setPoint(3, trp, (1<<temp[0])+(1<<temp[1]));
        }

        //Straight
        if (longest_straight>=5) {
            point.setPoint(4, ace_s, 0);
        }

        //FullHouse
        if (triples.size()==1 && pairs.size()>0) {
            int trp = *triples.begin();
            int pr = *(--pairs.end());
            point.setPoint(6, trp, pr);
        }
        if (triples.size()==2) {
            int trp = *(--triples.end());
            int pr = *triples.begin();
            if (pairs.size()>0) {
                int it = *(--pairs.end());
                pr = max(pr, it);
            }
            point.setPoint(6, trp, pr);
        }

        //Quad
        if (quad!=-1) {
            point.setPoint(7, quad, 0);
        }

        
        //-------------Check Type-----------------//
        bool have[4][13] = {false};
        int typ[4] = {0};

        for(Card c : cards) {
            typ[c.type]++;
            have[c.type][c.num] = true;
        }
        
        //Flush
        for(int i=0; i<4; i++) {
            if (typ[i]>=5) {
                int temp = 0;
                int cnt = 0;
                for(int j=12; j>=0; j++) {
                    if (!have[i][j]) continue;
                    temp += 1<<j;
                    cnt++;
                    if (cnt==5) break;
                }
                point.setPoint(5, temp, 0);
            }
        }
    }

};