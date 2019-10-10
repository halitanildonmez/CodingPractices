#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Zone
{
    int dist;
    int dur;
};
int calculate_v (int x, int t) 
{
    return x/t;
}
int main()
{
    int speed;
    cin >> speed; cin.ignore();
    int lightCount;
    cin >> lightCount; cin.ignore();
    
    cerr << "Max speed: " << speed << endl;
    int time_elapsed = 0;
    int v_out = speed;
    
    for (int i = 0; i < lightCount; i++) {
        int distance;
        int duration;
        cin >> distance >> duration; cin.ignore();
        cerr << "Distance and duration: " 
            << distance << " " << duration << endl;
        
        
        int current_time = duration - time_elapsed;
        cerr << "elapsed time from the light: " << current_time << endl;
        
        int v_cur = calculate_v(distance, duration);
        // we can use the max speed
        if (v_cur < speed)
            v_cur = speed;
            
        v_out = v_cur;
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << v_out << endl;
}