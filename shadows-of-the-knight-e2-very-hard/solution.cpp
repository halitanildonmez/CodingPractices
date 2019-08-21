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
    int area;
};

Zone* zonePtr;

enum State {
    WARM,
    COLD,
    SAME,
    INVALID
};

int blind_binary_search(int curMove, State state, int M, int &X0, int &Y0, int area, bool searchY, int &delta)
{
    cerr << "Mid: " << M << " - " << curMove << endl;
    switch (state)
    {
    case WARM:
        if (curMove == 1 && !searchY) {
            cerr << "CALC WARM ?" << endl;
            Y0 = area - 1;
        }
        else {
            if (!searchY)
            {
                cerr << "DELTA: " << delta << " " << X0 << " " << Y0 << endl;
                if (delta  > 0)
                    X0 = M + (1 * delta);   
                else
                    Y0 = M - 1;
            }
            else
            {
                X0 = M + (1 * delta);
            }
        }
        
        break;
    case COLD:
        if (curMove == 1 && !searchY) {
            cerr << "We came from 0 so go down..." << endl;
            Y0 = area - 1;
        }
        else if (curMove == 1 && searchY)
        {
            Y0 = M - 1;
        }
        else {
            cerr << "We should go back" << endl;
            //PlayZone prev = zones[curMove - 2];
            Zone prev = zonePtr[curMove - 2];
            cerr << "Revinding to L " << prev.low << " R: " << M << prev.mid << " + " << prev.high << endl;
            X0 = prev.low;
            Y0 = prev.mid;
            
            cerr << "Has to be between " << X0 << " and " << zonePtr[curMove - 1].mid << endl;
            Y0 = zonePtr[curMove - 1].mid;
            
            int tmpM = floor((X0 + Y0) / 2);
            
            if (tmpM - Y0 < 0)
            {
                cerr << "Delta should be -1 so we have to go opposite dir" << endl;
                delta = -1;
            }
        }
        break;
    case SAME:
    case INVALID:
    default:
        if (searchY)
        {
            X0 = 0;
            Y0 = area - 1;
        }
        else
        {
            X0 = 0;
            Y0 = 0;
        }
        break;
    }
    
    M = floor((X0 + Y0) / 2);
    Zone z;//(X0, M, Y0);
    z.low = X0;
    z.mid = M;
    z.high = Y0;
    z.area = area;
    cerr << "X0: " << X0 << " Y0: " << Y0 << " M: " << M << " " << z.area << endl;
    zonePtr[curMove] = z;
    return M;
}

int search_x(int curMove, State state, int M, int &X0, int &Y0, int area, bool searchY, int &delta)
{
    cerr << "Start: \ncurMove " << curMove << " X0: " << X0 << " Y0: " << Y0 << " M: " << M << " Area: " << 
                area << " Delta: " << delta << endl;
    Zone z;
    
    switch (state)
    {
        case WARM:
    
            return M;
        case COLD:
  
            return M;
        case SAME:
            return M;
        case INVALID:
            cerr << "Invalid set to 0\n";
            return 0;
        default:
            return -1;
    }
    return -1;
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
    
    int delta = 1;
    // game loop
    while (1) {
        string bombDir; // Current distance to the bomb compared to previous distance (COLDER, WARMER, SAME or UNKNOWN)
        cin >> bombDir; cin.ignore();
        
        if (searchX){
            cerr << "Move number: " << currentMove << 
                " low: " << low << " middle " << middle << " high " << 
                    high << endl;
        } else  {
            cerr << "Move number: " << ymoves << 
                " low y: " << low_y << " middle y: " << middle_y << " high y:" << 
                    high_y << endl;
        }
                
        if (low == high) {
            cerr << "Search X is found.\n";
            searchX = false;
            searchY = true;
        }
        
        if (low_y == high_y) {
            cerr << "Search Y is found.\n";
            searchY = false;
        }
        
        
        State s;
        if (bombDir == "WARMER")
        {
            cerr << "W" << endl;
            s = WARM;
            if (currentMove > 1 && searchX) {
                high = middle;
            }
            
            if (searchY && ymoves > 1) {
                high_y = middle_y;
            }
        }
        else if (bombDir == "COLDER")
        {
            cerr << "C" << endl;
            s = COLD;
            if (currentMove == 2)
                high = middle;
            else if (currentMove > 1)
                low = middle + 1;
            else if (currentMove == 1) {
                low = middle + 1;
            }
                
            if (searchY) {
                if (ymoves == 2)
                    high_y = middle_y;
                else if (ymoves > 1)
                    low_y = middle_y + 1;
            }
        }
        else if (bombDir == "SAME")
        {
            cerr << "S" << endl;
            s = SAME;
        }
        else
        {
            cerr << "I" << endl;
            s = INVALID;
            
        }
        
        if (searchX) 
        {
            //midX = search_x(currentMove, s, midX, x0, x1, W, false, delta);
            if (currentMove == 0)
                middle = 0;
            else
                middle = floor((low+high)/2);
        }
        else
        {
            //Y0 = blind_binary_search(currentMove, s, midY, y0, y1, H, true, delta);
            if (ymoves == 0)
                middle_y = 0;
            else
                middle_y = floor((low_y+high_y)/2);
            ymoves++;
        }
        
        if (searchX)
            cout << middle << " " << Y0 << endl;
        else if (searchY)
            cout << middle << " " << middle_y << endl;
        
        if (currentMove == 0) {
            middle =  floor((low+high)/2);
            diff_x = 0 - X0;
            cerr << "Diff X is " << diff_x << endl;
        }
        currentMove++;
        
        if (ymoves == 0) {
            middle_y = floor((low_y+high_y)/2);
            diff_y = 0 - Y0;
            cerr << "Diff X is " << diff_x << endl;
        }
    }
}

/**
        if (bombDir == "WARMER") {
            cerr << "W" << endl;
            if (currentMove == 1) {
                Y0 = total/2 - 1;
            }
            else {
                X0 = M + delta;    
            }
        } else if (bombDir == "COLDER") {
            cerr<<"C"<<endl;
            if (currentMove == 1) {
                cerr << "We came from 0 so go down..." << endl;
                Y0 = total-1;
            }
            else {
                cerr << "We should go back" << endl;
                Zone prev = zones[currentMove-2];
                cerr << "Revinding to L " << prev.low << 
                        " R: " << M << endl;
                if (prev.low == 0 && prev.high == 0)
                {
                    cerr << "Going back is the same positon" << endl;
                    Y0 = M - 1;
                }
                else 
                {
                    X0 = prev.low;
                    Y0 = prev.mid;   
                }
            }
        } else if (bombDir == "SAME") {
            cerr<<"S"<<endl;
            // TODO: change
            //delta = -1;
            X0 = M + delta;
            total = W;
            X0 = 0;
            Y0 = total/2 - 1;
            gX = X0;
            cerr << "Goal at " << X0 << endl;
            //currentMove = 0;
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
    
        if (gX != -1)
        {
            cout << M << " " << gX << endl;
        }
        else
        {
            cout << 0 << " " << M << endl;    
        }
        
        zones[currentMove++] = z;
*/