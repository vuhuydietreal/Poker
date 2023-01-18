//by vuhuydiet
#pragma once
#include<map>
#include<string>
using namespace std;

class Point {
private:
    int status;
    int A;
    int B;

    map<int, string> statusMap = {
        {0, "High Card"}, {1, "Pair"}, {2, "Two Pair"}, {3, "Three Of A Kind"}, {4, "Straight"}, 
        {5, "Flush"}, {6, "Full House"}, {7, "Four Of A Kind"}, {8, "Straight Flush"}
        };

public:
    Point() : status(0), A(0), B(0) {}
    Point(int status, int A, int B): status(status), A(A), B(B) {}

    void clear() {
        status = 0;
        A = 0;
        B = 0;
    }

    void setPoint(int s, int fi, int se) {
        status = s;
        A = fi;
        B = se;
    }

    string getStatus() {
        return statusMap[status];
    }


    bool operator< (Point b) {
        if (status<b.status || (status==b.status&&A<b.A)
         || (status==b.status&&A==b.A&&B<b.B)) 
            return true;
        return false;
    }
    bool operator== (Point b) {
        if (status==b.status && A==b.A && B==b.B)
            return true;
        return false;
    }
    bool operator> (Point b) {
        if (status>b.status || (status==b.status&&A>b.A)
         || (status==b.status&&A==b.A&&B>b.B)) 
            return true;
        return false;
    }

    friend Point max(Point a, Point b) {
        return a>b? a : b;
    }
};