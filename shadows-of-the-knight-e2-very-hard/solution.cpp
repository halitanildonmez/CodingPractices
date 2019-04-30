#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

struct Point2D
{
    float x;
    float y;
    Point2D (int cx, int cy):x(cx), y(cy) {}
};

bool withinBound (int val, int bound) {
    return val < bound;
}

int to1DCoord (int x, int y, int w) {
    return (x) + (y*w);
}

Point2D to2DCoord (int i, int w) {
    int x = i / w;
    int y = i % w;
    return Point2D(x, y);
}
// ---------- PRINT STATEMENTS ---------------
void debugPoint(Point2D p) {
    cerr << p.x << " " << p.y << endl;
}
// -------------------------------------------

void printRes (int m, int w) {
    Point2D output = to2DCoord(m, w);
    cout << output.x << " " << output.y << endl;
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
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
    cerr << W << " " << H << endl;
    
    int l = 0;
    int r = (W*H) - 1;
    int dx = X0;
    int dy = Y0;
    
    int m = 0;
    Point2D output = Point2D(X0, Y0);
    // https://stackoverflow.com/questions/1449713/representing-a-2d-array-as-a-1d-array
    // game loop
    while (1) {
        string bombDir; // Current distance to the bomb compared to previous distance (COLDER, WARMER, SAME or UNKNOWN)
        cin >> bombDir; cin.ignore();
        
        if (bombDir == "COLDER") {
            cerr << "COLDER" << endl;
            l = m + 1;
            m = floor((l+r)/2);
            printRes (m, W);
        } else if (bombDir == "WARMER") {
            cerr << "WARMER " << endl;
            r = m - 1;
            m = floor((l+r)/2);
            printRes (m, W);
        } else if (bombDir == "SAME") {
            cerr << "SAME " << X0 << " - " << Y0 << endl;
            l = m + 1;
            m = floor((l+r)/2);
            printRes (m, W);
        } else {
            cerr << "Default " << endl;
            // will enter here only once (on the start)
            m = floor((l+r)/2);
            printRes(m, W);
        }
    }
}