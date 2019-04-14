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

struct Bound {
    int start, end;
    Bound (int s, int e):start(s), end(e) {}
};

Point2D trilateral (Point2D p1, Point2D p2, Point2D p3, float r1, float r2,
                    float r3)
{
    float x = (r1*r1 - r2*r2 + p2.x*p2.x) / (2*p2.x);
    float y = (r1*r1 - r3*r3 + p3.x*p3.x + p3.y*p3.y - 2*p3.x*x) / (2*p3.y);
    return Point2D(x,y);
}

Point2D boxApp (int X0, int Y0, int W, int H, int sizeX, int sizeY)
{
    int b1 = X0 + sizeX;
    int b2 = Y0 + sizeY;
    if (b1 > W)
        b1 = W-1;
    if (b2 > H)
        b2 = H-1;
    return Point2D(b1,b2);
}

bool withinBound (int val, int bound) {
    return val < bound;
}

void debugPoint(Point2D p) {
    cerr << p.x << " " << p.y << endl;
}

int to1DCoord (int x, int y, int w) {
    return x + (w*y);
}
Point2D to2DCoord (int i, int w) {
    int x = i % w;
    int y = i / w;
    return Point2D(x, y);
}

void debugBound(Bound p, int w) {
    debugPoint(to2DCoord(p.start, w));
    debugPoint(to2DCoord(p.end, w));
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
    
    Point2D area(W, H);
    int midX = W / 2;
    int midY = H / 2;
    bool isCold = false;
    
    cerr << W << " " << H << endl;
    
    int pos_index = to1DCoord(W, H, W);
    int R = pos_index/2;
    int max = W*H - 1;
    Bound leftBound(0, (pos_index/2));
    Bound rightBound((pos_index/2 + 1), max);
    
    debugBound(leftBound, W);
    debugBound(rightBound, W);
    // game loop
    while (1) {
        string bombDir; // Current distance to the bomb compared to previous distance (COLDER, WARMER, SAME or UNKNOWN)
        cin >> bombDir; cin.ignore();
        
        int curIndex = to1DCoord(X0, Y0, W);
        
        if (bombDir == "COLDER") {
            cerr << "COLDER" << endl;
            isCold = true;
            // 0, 1
            debugPoint(Point2D(midX,midY));
            
        } else if (bombDir == "WARMER") {
            cerr << "WARMER" << endl;
            area = Point2D(X0, Y0);
            debugPoint(area);
            //X0 = midX;
            //Y0 = midY;
            
            // go to mid of right bound and update the bounds
            
            // if we are at an invalid place we need to look at the mid of 
            // cur index and the rigth bound
            if (!withinBound(rightBound.start + rightBound.start/2, max)) {
                cerr << "wont " << endl;
                int tmp = to1DCoord(X0, Y0, W) + rightBound.start;
                rightBound = Bound(tmp/2 + 1, max);
            } else {
                rightBound = Bound(rightBound.start + rightBound.start/2, max);    
            }
            
        } else if (bombDir == "SAME") {
            cerr << "SAME" << endl;
        }

        if (!isCold) {
            midX /= 2;
            midY /= 2;   
            if (!withinBound(midX, W))
                midX = W - 1;
            if (!withinBound(midY, H))
                midY = H - 1;
            
            // go to center of right bound
            Point2D test = to2DCoord(rightBound.start, W);
            if (withinBound(rightBound.start + rightBound.start/2, max)) {
                X0 = test.x;
                Y0 = test.y;
            }
            cout << test.x << " " << test.y << endl;
        } else {
            midX++;
            cout << midX << " " << midY << endl;
        }
    }
}

        /*
        Point2D tri = boxApp(X0, Y0, W, H, bx, by);
        X0 = tri.x;
        Y0 = tri.y;
        cout << tri.x << " " << tri.y << endl;
        */
        /*
        Point2D tri = trilateral(p1, p2, p3, 3.f, 1.f, 1.f);
        cout << tri.x << " " << tri.y << endl;
        */