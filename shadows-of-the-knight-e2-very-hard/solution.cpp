#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

struct Move {
    int l;
    int r;
    int m;
    // 0 cold, 1 warm, 2 same
    int type;
    int left; // 0 => left 1 => right
};

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
void debugMove (Move m, int w) {
    cerr << "DEBUG MOVE " << endl;
    debug1DPoint(m.l, w);
    debug1DPoint(m.m, w);
    debug1DPoint(m.r, w);
    cerr << m.left << " - " << m.type << endl;
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
    
    Move moves[N];
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
        int type = 0;
        int isLeft = 0;
        
        if (bombDir == "COLDER") {
            cerr << "COLDER" << endl;
            isLeft = 0;
            //cerr << "total dist is " << totalDist << endl;
            if (isUpDown) {
                // the output distance
                r = m;
                // wrong! Should go back last warm - distance somehow
                l = midPoint;
                //l = lastWarmPosition; //(wrong)
            } else {
                // should have gone right from the last right
                // also we have to go back like 2 moves
                if (moveCount > 0) {
                    // we are cold that is the current move
                    Move lastWarm = moves[moveCount-1];
                    cerr <<"Peek mid; "<< moves[moveCount-1].m << " " << m << endl;
                    
                    Move tm = lastWarm;
                    int tm_i = moveCount-1;
                    while (tm.m == m && tm_i >= 0) {
                        --tm_i;
                        tm = moves[tm_i];
                    }
                    
                    cerr << tm.left << endl;
                    if (tm.left == 1)
                    {
                        l = m + 1;
                    }
                    else 
                    {
                        l = tm.m + 1;
                        r = tm.r;
                    }
                    
                }
                /*l = lastWarmPosition + 1;
                cerr << moveCount << endl;
                if (moveCount > 0)
                    r = moves[moveCount-2];*/
            }
            
        } else if (bombDir == "WARMER") {
            isLeft = 1;
            type = 1;
            cerr << "WARMER " << endl;
            wasWarm = true;
            if (isUpDown) {
                l = m + 1;
            } else {
                r = m - 1;
            }
        } else if (bombDir == "SAME") {
            type = 2;
            cerr << "SAME " << X0 << " - " << Y0 << endl;
            l = m + 1;
        } else {
            
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
        
        cerr << "Mid " << m << endl;
        
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
        
        Move madeMove;
        madeMove.l = l;
        madeMove.r = r;
        madeMove.m = m;
        madeMove.type = type;
        madeMove.left = isLeft;
        
        debugMove(madeMove, W);
        
        moves[moveCount] = madeMove;
        moveCount++;
    }
}