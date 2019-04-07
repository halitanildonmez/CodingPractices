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

Point2D trilateral (Point2D p1, Point2D p2, Point2D p3, float r1, float r2,
                    float r3)
{
    float x = (r1*r1 - r2*r2 + p2.x*p2.x) / (2*p2.x);
    float y = (r1*r1 - r3*r3 + p3.x*p3.x + p3.y*p3.y - 2*p3.x*x) / (2*p3.y);
    return Point2D(x,y);
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

    Point2D p1(0,0);
    Point2D p2(W,0);
    Point2D p3(X0,H);
    
    // game loop
    while (1) {
        string bombDir; // Current distance to the bomb compared to previous distance (COLDER, WARMER, SAME or UNKNOWN)
        cin >> bombDir; cin.ignore();
        
        if (bombDir == "COLDER"){
            cerr << "COLDER" << endl;       
        }
        else if (bombDir == "WARMER"){
            cerr << "WARMER" << endl;
            p2 = Point2D(X0, 0);
            
        }
        else if (bombDir == "SAME") {
            cerr << "SAME" << endl;
        }

        Point2D tri = trilateral(p1, p2, p3, 3.f, 1.f, 1.f);
        cout << tri.x << " " << tri.y << endl;
    }
}