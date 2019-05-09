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
    int y = i / w;
    int x = i % w;
    return Point2D(x, y);
}

float EuclidianDistance (Point2D p1, Point2D p2) {
    float A = abs(p2.x - p1.x);
    float B = abs(p2.y - p1.y);
    float AB = (A*A) + (B*B);
    return sqrtf(AB);
}

float Euclidian1D (int i1, int i2, int w)  {
    return EuclidianDistance(to2DCoord(i1, w), to2DCoord(i2, w));
}
// ---------- PRINT STATEMENTS ---------------
void debugPoint(Point2D p) {
    cerr << p.x << " " << p.y << endl;
}
void debug1DPoint(int p, int w) {
    debugPoint(to2DCoord(p, w));
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
    
    int moves[N];
    int moveCount = 0;
    
    int l = 0;
    int r = (W*H) - 1;
    
    /**
        thinking of Jack Sparrow for some reason. we need to know the direction of 
        which we have to update the left and right. 
        if true:
            on warm => update left
            on cold => update right
        if false:
            default behaviour
    */
    bool isUpDown = false;
    
    int midPoint = floor((l+r)/2);
    int startIndex = to1DCoord(X0, Y0, W);
    int sep = startIndex;
    if (startIndex < midPoint) {
        cerr << "up is down" << endl;
        cerr << "dist " << Euclidian1D(startIndex, midPoint, W) << endl;
        
        isUpDown = true;
    }
    
    int totalDist = 0;
    int lastWarmPosition = midPoint;
    int m = 0;
    // game loop
    while (1) {
        string bombDir; // Current distance to the bomb compared to previous distance (COLDER, WARMER, SAME or UNKNOWN)
        cin >> bombDir; cin.ignore();
        
        bool wasWarm = false;
        
        if (bombDir == "COLDER") {
            cerr << "COLDER" << endl;
            debug1DPoint(lastWarmPosition, W);
            cerr << "total dist is " << totalDist << endl;
            if (isUpDown) {
                // the output distance
                r = m;
                // wrong! Should go back last warm - distance somehow
                l = midPoint;
                //l = lastWarmPosition; //(wrong)
            } else {
                // should have gone right from the last right
                l = lastWarmPosition + 1;
                cerr << moveCount << endl;
                if (moveCount > 0)
                    r = moves[moveCount-2];
            }
            
        } else if (bombDir == "WARMER") {
            cerr << "WARMER " << endl;
            wasWarm = true;
            if (isUpDown) {
                l = m + 1;
            } else {
                r = m - 1;
            }
        } else if (bombDir == "SAME") {
            cerr << "SAME " << X0 << " - " << Y0 << endl;
            l = m + 1;
        } else {
            cerr << "Default " << endl;
            // enter here on first try
        }
        cerr << "Calculating mid between \nLeft:";
        debug1DPoint(l, W);
        cerr << "And Right:";
        debug1DPoint(r, W);
        // calculate the mid point
        m = floor((l+r)/2);
        // print the result
        printRes (m, W);
        // calculate the distance to the last posint 
        // currently for debugging only
        startIndex = to1DCoord(X0, Y0, W);
        cerr << "dist final: " << Euclidian1D(m, startIndex, W) << endl;
        
        // update the last position where we were warmer
        if (wasWarm) {
            totalDist += Euclidian1D(m, startIndex, W);
            lastWarmPosition = to1DCoord(X0, Y0, W);
            startIndex = r;
        }
        // update to the current position
        Point2D dest = to2DCoord(m, W);
        X0 = dest.x;
        Y0 = dest.y;
        
        moves[moveCount] = r;
        moveCount++;
    }
}