#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

struct zone {
    int l, m, h;
};

void debugzone (zone z, string m) {
    cerr << m << "\n" << z.l << " " << 
        z.m << " " << z.h << "" << endl; 
}

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
    
    // the zones
    zone cold = {0, (X0-1)/2, W - 1};
    zone warm = {0, (X0+1)/2, W - 1};
    // move to make
    zone current = {0, 0, W - 1};
    int pos = X0;
    int limit = W - 1;
    
    bool out = false;
    bool search_x = true;
    bool search_y = false;
    
    // have to place here because the labels does not allow to have the initializations somewhere else
    int give = 0;
    int low = 0;
    int high = 0;
    int mid = 0;
    int lower = 0;
    int higher = 0;
    
    bool first = true;
    
    // game loop
    while (1) {
        string bombDir;
        cin >> bombDir; cin.ignore();
   
        if (bombDir == "COLDER") {
            cerr << bombDir << endl;
            current = {cold.l, 0, cold.h};
        } else if (bombDir == "WARMER") {
            cerr << bombDir << endl;
            current = {warm.l, 0, warm.h};
        } else if (bombDir == "SAME") {
            cerr << bombDir << endl;
            if (!first) {
                first = true;
                if (search_x) {
                    search_x = false;
                    X0 = ((current.l + current.h)/2);
                    cold = {0, 0, H - 1};
                    warm = {0, 0, H - 1};
                    current = {0, 0, H - 1};
                    limit = H - 1;
                    pos = Y0;
                    goto printresult;
                }
                else {
                    Y0 = (current.l + current.h)/2;
                    goto printresult;
                }   
            }
        } else if (bombDir == "UNKNOWN") {
            cerr << bombDir << endl;
        }
        
        if (current.l >= current.h) {
            first = true;
            if (search_x) {
                search_x = false;
                X0 = ((current.l + current.h)/2);
                cold = {0, 0, H - 1};
                warm = {0, 0, H - 1};
                current = {0, 0, H - 1};
                limit = H - 1;
                pos = Y0;
                goto printresult;
            }
            else {
                Y0 = (current.l + current.h)/2;
                goto printresult;
            }
        }
        first = false;
        
        low = current.l;
        high = current.h;
        give = low + high - pos;
        
        if (out) {
            if (pos == 0) {
                give  = int((give-0) / 2);
            } else if (pos == limit) {
                give = int(limit+give)/2;
            }
        }
        
        out = false;
        if (give == pos) {
            give = pos + 1;
        }
        if (give < 0) {
            give = 0;
            out = true;
        }
        else if (give > limit) {
            give = limit;
            out = true;
        }
        
        mid = (give + pos)/2;
        lower = (give + pos - 1)/2;
        higher = (give + pos + 1)/2;
        
        if (give > pos) {
            cold = {low, 0, lower};
            warm = {higher, 0, high};
        }
        else if (give < pos) {
            cold = {higher, 0, high};
            warm = {low, 0, lower};
        }
        
        if (search_x) {
            X0 = give;
            pos = X0;
        }
        else {
            Y0 = give;
            pos = Y0;
        }
printresult:
        cout << X0 << " " << Y0 << endl;
    }
}