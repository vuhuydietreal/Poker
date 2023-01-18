//by vuhuydiet
#include<fstream>
#include<string>

#include "Account.cpp"

struct Info {
    string name;
    string password;
    string money;

    Info() {}
    Info(string name, string password, string money) : name(name), password(password), money(money) {}
};

Info getInfo(string line) {
    Info acc;

    int state = 0;
    for(int i=0; i<line.length(); i++) {
        if (line[i]==' ') {
            state++;
            continue;
        }
        if (state==0) {
            acc.name += line[i];
        }
        else if (state==1) {
            acc.password += line[i];
        }
        else {
            acc.money += line[i];
        }
    }

    return acc;
}

int string_to_int(string str) {
    int res = 0;
    int n = str.length();
    for(int i=0; i<n; i++) {
        int x = str[i] - '0';
        res = res*10 + x;
    }

    return res;
}

Info Login() {
    string name;
    string password;

    bool noAcc = false;
    bool wrongPass = false;
    do {
        system("cls");
        if(noAcc) cout << "Your account has not been registered.\n";
        if (wrongPass) cout << "Wrong password.\n";
        cout << "Press & to return.\n";
        cout << "Enter your account: \n\n";

        cout << "Account: "; cin >> name;
        if (name=="&") return Info("&return", "", "");
        cout << "Password: "; cin >> password;

        noAcc = false;
        wrongPass = false;

        fstream in;
        in.open("account.txt", ios::in);
        string line;
        while(getline(in, line)) {
            Info acc = getInfo(line);

            if (acc.name==name) {
                if (acc.password==password) {
                    in.close();
                    return acc;
                }
                else {
                    wrongPass = true;
                    break;
                }
            }
        }
        in.close();

        if(!wrongPass) noAcc = true;
    } while(true);
}

bool Register() {
    string name;
    string password;

    bool exist = false;
    bool success = true;
    do {
        system("cls");
        if (exist) cout << "This user name has already been registered. Please try another name.\n";
        if (!success) cout << "Only accept characters a-z and 0-9\n";
        cout << "Press & to return.\n";
        cout << "Create your new account: \n\n";

        cout << "Account: "; cin >> name;
        if (name=="&") return false;
        cout << "Password: "; cin >> password;

        exist = false;
        success = true;
        for(int i=0; i<name.length(); i++) {
            if (name[i]<'0' || (name[i]>'9'&&name[i]<'a') || name[i]>'z') {
                success = false;
            }
        }
        for(int i=0; i<password.length(); i++) {
            if (password[i]<'0' || (password[i]>'9'&&password[i]<'a') || password[i]>'z') {
                success = false;
            }
        }

        string line;
        fstream in;
        in.open("account.txt", ios::in);
        while (getline(in, line)) {
            Info acc = getInfo(line);

            if (acc.name == name)
                exist = true;
        }
        in.close();
    } while(!success || exist);

    fstream out;
    out.open("account.txt", ios::app);
    out << name << " " << password << " " << "100000" << "\n";
    out.close();

    return true;
}

Account log() {
    char action;

    bool valid = true;

    bool RegSuc = false;
    
    do {
        system("cls");
        if (!valid) cout << "Invalid action!\n";
        
        if (RegSuc) cout << "Your account has been registered. Press 'L' to login.\n";
        
        cout << "Press 'L' to login your account or 'R' to register if you do not have one already.\n";

        RegSuc = false;
        cin >> action;
        if (action=='L' || action=='l') {
            Info acc = Login();

            if (acc.name!="&return")
                return Account(acc.name, string_to_int(acc.money));
            valid = true;
        }
        else if (action=='R' || action=='r') {
            RegSuc = Register();
            valid = true;
        }
        else
            valid = false;
    } while(true);
}