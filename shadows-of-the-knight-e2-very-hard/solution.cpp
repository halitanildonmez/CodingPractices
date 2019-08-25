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

struct Interval {
    int cl;
    int ch;
    int wl;
    int wh;
};
Interval *intervals;

struct Zone {
    int low;
    int mid;
    int high;
    int area;
};

Zone* zonePtr;

enum State {
    WARM,
    COLD,
    SAME,
    INVALID
};


void dd (Zone z, string msg) {
    cerr << msg << "\t\n" << z.low << " " << z.mid << " " << z.high << endl;
}

void deg (Interval i, string m) {
    cerr << m << "\n"<< i.cl << " " << i.ch << " " << i.wl << " " << i.wh << endl;
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

    zonePtr = new Zone[N];
    int currentMove = 0;
    int ymoves = 0;
    
    bool searchX = W > 1 ? true : false;
    bool searchY = false;
    int midX = 0;
    int midY = 0;
    int x0, x1, y0, y1;
    
    // Regular BS(LOL) test Variables
    int low, middle, high;
    low = 0;
    high = W - 1;
    
    int low_y, middle_y, high_y;
    low_y = 0;
    high_y = H - 1;
    
    int diff_x, diff_y;
    diff_x = diff_y = 0;
    // BS End (LOL)
    
    /*
    Two cases: 
    1: After setting to 0 you get Cold
        Means that target is (mid, high)
         AND you should go to right
    2: After setting to 0 you get Warm
        Means that target is (0, mid)
         AND you should go left
    */
    bool isCase1 = true;
    
    /*
    If this counter is 2 this means that we should 
    rewind to the previous moves
    */
    int yColdCount = 0;
    
    int delta = 1;
    
    // test
    int lowTest = 0;
    int midTest = 0;
    int highTest = W;
    Zone currentZone;

    
    Interval current;
    current.cl = 0;
    current.ch = X0-1;
    current.wl = current.ch + 1;
    current.wh = W-1;
    intervals = new Interval[N];
    bool first = true;
    
    Zone cold;
    cold.low = 0;
    cold.high = W/2;
    cold.mid = 0;
    
    Zone warm;
    warm.low = cold.high+1;
    warm.high = W-1;
    
    Zone outputZone;
    outputZone.low = W/2;
    outputZone.high = W-1;
    
    // game loop
    while (1) {
        string bombDir; // Current distance to the bomb compared to previous distance (COLDER, WARMER, SAME or UNKNOWN)
        cin >> bombDir; cin.ignore();

        if (warm.low == warm.high && searchX) {
            cerr << "Found X at " << X0 << endl;
            searchX = false;
            searchY = true;
            currentMove = 0;
            
            cold.low = 0;
            cold.high = H/2;
            cold.mid = 0;
            
            warm.low = cold.high+1;
            warm.high = H-1;
            
            outputZone.low = H/2;
            outputZone.high = H-1;
        }
        
        dd(cold, "Cold ");
        dd(warm, "Warm ");
        cerr << "Current move: " << currentMove << " X0: " << X0 << " Y0: "<< Y0 << endl;
        
        State s;
        if (bombDir == "WARMER")
        {
            cerr << "W" << endl;
            s = WARM;
            if ((X0 == 0 && searchX) || (searchY && currentMove == 1)){
                cerr << "Try the warm interval now\n";
                outputZone.low = warm.low;
                outputZone.high = warm.high;
                warm.high = cold.high;
                cold.high = (cold.high/2);
                warm.low = cold.high + 1;
            } else if (searchY && currentMove == 0) {
                cerr << "First move for Y\n";
                outputZone.low = warm.low;
                outputZone.high = warm.high;
            } else if (searchY) {
                if (currentMove == 2) {
                    cerr << "Coming from 0\n";
                    outputZone = warm;
                } else {
                    int tt = ((cold.low+cold.high)/2);
                    if (Y0 == tt) {
                        cerr << "WW came from cold so try warm\n";
                        if (currentMove > 2) {
                            /*Zone tmpt = cold;
                            cold.high = ((cold.low+cold.high)/2);
                            warm.low = cold.high + 1;
                            warm.high = tmpt.high;*/
                        }
                        outputZone = warm;
                    } else {
                        // came from warm so try cold
                        warm.high = cold.high;
                        warm.low = ((cold.low+cold.high)/2) + 1;
                        cold.high = warm.low - 1;
                        outputZone = cold;
                    }   
                }
            } else {
                // try the warm interval now
                Zone tmp = cold;
                Zone tmp2 = warm;
                if (cold.high != 1) {
                    cold.high = (cold.high/2);
                    warm.low = cold.high + 1;
                    warm.high = tmp.high;
                    outputZone = warm;   
                } else {
                    cold.low = cold.high;
                    outputZone = cold;
                }
            }
        } else if (bombDir == "COLDER") {
            cerr << "C" << endl;
            s = COLD;
            // this means we should update te warm part
            if ((currentMove == 1 && searchX)) {
                cerr << "Try 0 to cut properly\n";
                outputZone.low = 0;
                outputZone.high = 0;
                cold.high = (cold.high/2);
                warm.low = cold.high+1;
                warm.high = (W/2) - 1;
            } else if (searchY) {
                int tt = ((cold.low+cold.high)/2);
                if (Y0 == tt) {
                    cerr << "CC came from cold so try warm\n";
                    cold.low = warm.low;
                    cold.high = ((warm.low+warm.high)/2);
                    warm.low = cold.high + 1;
                    outputZone = warm;
                } else {
                    cerr << "CC came from WARM so try cold 2\n";
                    if (Y0 == 0) {
                        cold.low = warm.low;
                        cold.high = ((warm.low+warm.high)/2);
                        warm.low = cold.high + 1;
                        outputZone = warm;
                    } else {
                        // came from warm so try cold
                        warm.high = cold.high;
                        warm.low = ((cold.low+cold.high)/2) + 1;
                        cold.high = warm.low - 1;
                        outputZone = warm;                 
                    }
                }
            } else {
                cerr << "We tried the warm interval\n";
                // try the cold interval now
                if (cold.low == cold.high) {
                    cerr << "No more to try for cold\n";
                    Zone tmp = warm;
                    cold.low = tmp.low;
                    cold.high = ((tmp.low+tmp.high)/2);
                    warm.low = cold.high + 1;
                    warm.high = tmp.high;
                }
                outputZone = warm; 
            }
        } else if (bombDir == "SAME") {
            cerr << "S" << endl;
            s = SAME;
        } else {
            cerr << "I" << endl;
            s = INVALID;
        }
        
        if (currentMove == 1 && searchY)
            outputZone.low = outputZone.high = 0;
        
        // calculate the mid 
        outputZone.mid = floor((outputZone.low + outputZone.high)/2);
        // output mid for x or y
        if (searchX)
            X0 = outputZone.mid;
        else
            Y0 = outputZone.mid;
        
        // print result
        cout << X0 << " " << Y0 << endl;
        // update the interval and the current zone
        // this is just in case
        intervals[currentMove] = current;
        zonePtr[currentMove] = outputZone;
        currentMove++;
        // no longer the first move
        first = false;
    }
}