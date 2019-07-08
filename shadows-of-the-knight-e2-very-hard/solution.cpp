#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

struct Zone {
    int low;
    int mid;
    int high;
};

int main()
{
    int W; // width of the building.
    int H; // height of the building.
    cin >> W >> H; cin.ignore();
    int N; // maximum number of turns before game over.
    cin >> N; cin.ignore();
    int X0;
    int Y0;
    cin >> X0 >> Y0; cin.ignore();

    int M = 0;

    int lp = 0;
    int hp = H - 1;
    
    bool ll = false;

    Zone zones[N];
    int currentMove = 0;

    // game loop
    while (1) {
        string bombDir; // Current distance to the bomb compared to previous distance (COLDER, WARMER, SAME or UNKNOWN)
        cin >> bombDir; cin.ignore();
        cerr << "Move index: " << currentMove << endl;

        if (bombDir == "WARMER") {
            cerr << "W" << endl;
            X0 = M + 1;
            
        } else if (bombDir == "COLDER") {
            cerr<<"C"<<endl;
            if (currentMove == 1) {
                cerr << "We came from 0 so go down..." << endl;
                Y0 = H-1;
            }
            else {
                cerr << "We should go back" << endl;
                Zone prev = zones[currentMove-2];
                cerr << "Revinding to L " << prev.low << 
                        " R: " << M << endl;
                X0 = prev.low;
                Y0 = prev.mid;
            }
        } else if (bombDir == "SAME") {
            cerr<<"S"<<endl;
        } else {
            // First move start from 0
            X0 = 0; 
            Y0 = 0;
            ll = true;
        }

        Zone z;
        z.low = X0;
        z.high = Y0;
        
        M = floor((X0+Y0)/2);
        z.mid = M;
        cerr << "X0: " << X0 << " Y0: " << Y0 << " M: " << M << endl;
        
        cout << "0 " << M << endl;
        zones[currentMove++] = z;
    }
}