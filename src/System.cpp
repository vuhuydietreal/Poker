//by vuhuydiet
#include<stdlib.h>
#include "Deck.cpp"
#include "TableCards.cpp"
#include "Account.cpp"
#include "Player.cpp"
using namespace std;

class System {
private:
    Deck deck;
    TableCards table;
    int pot;

    int n;
    Player** players;
    bool* folded;
    int num_of_folded;
    int first;

public:
    System(Player** p, int n, int first) : n(n), pot(0), num_of_folded(0), first(first) {
        system("cls");

        deck = Deck(true);

        players = p;
        folded = new bool[n];
        for(int i=0; i<n; i++) {
            players[i]->newGame();
            folded[i] = false;
        }
    }

    //Playing
    void run() {
        for(int i=1; i<=4; i++) {
            switch(i) {
                case 1:
                    pre_flop();
                    break;
                case 2:
                    flop();
                    break;
                case 3:
                    turn();
                    break;
                case 4:
                    river();
                    break;
            }

            playersAction(first);

            if (num_of_folded==n-1) {
                result();
                return;
            }
        }

        result();
    }

    void pre_flop() {
        for(int i=0; i<n; i++) {
            Card a = deck.draw();
            Card b = deck.draw();
            players[i]->pre_flop(a, b);
        }
    }
    void flop() {
        Card a = deck.draw();
        Card b = deck.draw();
        Card c = deck.draw();

        table.flop(a, b, c);

        for(int i=0; i<n; i++) {
            players[i]->flop(a, b, c);
        }
    }
    void turn() {
        Card a = deck.draw();

        table.turn(a);

        for(int i=0; i<n; i++) {
            players[i]->turn(a);
        }
    }
    void river() {
        Card a = deck.draw();

        table.river(a);

        for(int i=0; i<n; i++) {
            players[i]->river(a);
        }
    }
    
    void endGame() {
        delete[] folded;
    }
    
    //Result
    void result() {
        system("cls");
        if (table.num_of_cards>0) {
            table.display(); cout << "\n\n";
        }
        for(int i=0; i<n; i++) {
            cout << players[i]->userName << ": ";
            players[i]->hand.display(); cout << "\n";
        }

        vector<int> winners = getWinners();
        int price = pot/winners.size();
        for(int i : winners) {
            players[i]->setMoney(price);
            cout << "\nCongrats " << players[i]->userName << " on winning $"
            << price << " with " << players[i]->getStatus() <<"!";
        }
        cout << "\n\n\n";
        for(int i=0; i<n; i++) {
            players[i]->display();
            cout << "\n";
        }
    }
    vector<int> getWinners() {
        vector<int> winners;

        if (num_of_folded==n-1) {
            for(int i=0; i<n; i++) {
                if (folded[i]) continue;
                winners.push_back(i);
            }
            return winners;
        }

        Point best;
        for(int i=0; i<n; i++) {
            best = max(best, players[i]->getPoint());
        }
        for(int i=0; i<n; i++) {
            if (best==players[i]->getPoint()) {
                winners.push_back(i);
            }
        }

        return winners;
    }


    void playersAction(int first) {
        for(int i=0; i<n; i++) {
            players[i]->curBet = 0;
        }

        int roundBet = 0;
        int bet[n] = {0};
        bool ok[n] = {false};
        int i = first - 1;
        while(true) {
            i++; if (i==n) i = 0;

            if (folded[i]) continue;
            if (ok[i] && roundBet==bet[i]) break;
            ok[i] = true;

            int b = players[i]->action(table, pot, roundBet);
            
            if (b<0) {
                folded[i] = true;
                num_of_folded++;
                if (num_of_folded==n-1) return;
                continue;
            }
            bet[i] += b;
            roundBet = bet[i];
            pot += b;
        }
    }
    
};