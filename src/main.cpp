//by vuhuydiet
#include<iostream>
#include<string>
#include<map>
using namespace std;

#include "LoginAndRegister.cpp"
#include "Account.cpp"
#include "Person.cpp"
#include "Robot.cpp"
#include "System.cpp"

void inGame(Player** players, int n, int first) {
    System gameSystem(players, n, first);
    gameSystem.run();
    gameSystem.endGame();
}

void updateInfo(Account account) {
    vector<string> lines;
    
    string line;
    ifstream file("account.txt");
    while(getline(file, line)) {
        Info info = getInfo(line);
        if (info.name==account.userName) {
            string change;
            change += info.name + " " + info.password + " " + to_string(account.money);
            lines.push_back(change);
        }
        else 
            lines.push_back(line);
    }
    file.close();

    fstream out;
    out.open("account.txt", ios::out);
    for(string account : lines) {
        out << account << "\n";
    }
    out.close();
}

void getPlayersInGame(Account playerAccount) {
    //---------------Get Mode-----------------//
    char type;
    bool valid = true;
    bool pvp = false;
    do {
        system("cls");
        if (!valid) cout << "Invalid Mode\n";
        if (pvp) cout << "vl game offline ma doi pvp a\nchon pve di!!!\n";
        cout << "Chose Game Mode:\n\n";
        cout << "1. PvP          2. PvE\n";

        cin >> type;
        if (type == '1') {
            valid = true;
            pvp = true;
        }
        else if (type=='2') {
            valid = true;
            pvp = false;
        }
        else {
            valid = false;
        }
    } while(!valid || pvp);


    //-----------Get Number of Bot----------------//
    int nBot;
    valid = true;
    do {
        system("cls");
        if (!valid) cout << "Invalid Number of Bot\n";
        cout << "Number of Bot you want to have (between 1 and 5): ";

        cin >> nBot;
    } while(nBot<1 || nBot>5);

    //----------------Construct Players---------------------//
    Player** players = new Player*[nBot+1];

    players[0] = new Person(playerAccount);
    for(int i=1; i<nBot+1; i++) {
        string Rname = "Bot" + to_string(i);
        players[i] = new Robot(Account(Rname, 100000000));
    }

    //-------------Game------------------//
    int first = 0;
    char ctn = 'N';
    do{
        if (ctn=='N') cout << "Press 'S' to get in the game.\n";
        if (ctn=='N') cin >> ctn;

        inGame(players, nBot+1, first);
        playerAccount = *players[0];
        updateInfo(playerAccount);
        if (playerAccount.money==0) {
            cout << "You have no money.\nPress any key to exit.\n";
            char ex; cin >> ex;
            break;
        }

        first++; if (first==nBot+1) first = 0;

        cout << "Press 'C' to get to the next game or any other key to exit.\n";
        cin >> ctn;
    } while(ctn=='C' || ctn=='c');

    //-----------Delete-------------//
    delete[] players;
}

void getAccount() {
    Account playerAccount = log();
    if (playerAccount.money==0) {
        system("cls");
        cout << "You have no money.\nPress any key to exit.\n";
        char ex; cin >> ex;
        return;
    }
    getPlayersInGame(playerAccount);
}

int main() {
    system("cls");
    cout << "Welcome to the game!\n\nPress any key to continue!\n";
    char x; cin >> x;

    char cnt;
    do {
        getAccount();
        
        system("cls");
        cout << "Press 'L' to login or any other key to exit the game.\n";
        cin >> cnt;
    } while(cnt=='L' || cnt=='l');
}