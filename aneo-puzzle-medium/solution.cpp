#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
#include <list>

using namespace std;

// Zone structure, has duration, distance and 
// all the speed values, Size is some large value
// though is not needed 
// 
struct Zone
{
    Zone()
    {
        duration = 0;
        distance = 0;
        time_speed = nullptr;
        speeds = std::list<double>(500);
    }
    int duration;
    int distance;
    double* time_speed;
    std::list<double> speeds;
};

// check if the given duration will be within green light
// interval 
bool is_within_green(int t_cur, int t_max)
{
    int y = t_cur / t_max;
    return y % 2 == 0;
}
/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    int speed;
    cin >> speed; cin.ignore();
    int lightCount;
    cin >> lightCount; cin.ignore();
    
    // number of lights, could have been named
    // better
    Zone* zones = new Zone[lightCount];
    // index starts from 0 but we need the last value
    // so for max speed 50, we need the index 50
    const int speed_value_size = speed + 1;
    // convert the speed limit to m/s
    const double v_max_ms = (speed * 10.0) / 36.0;
    
    for (int i = 0; i < lightCount; i++) {
        int distance;
        int duration;
        cin >> distance >> duration; cin.ignore();
        
        zones[i].distance = distance;
        zones[i].duration = duration;
        // index at 50 is 49 so we need the extra size
        zones[i].time_speed = new double[speed_value_size];
        
        // distance is starting from the start point
        // so we need to substract from the previous point 
        // to know the exact distance
        if (i > 0)
            distance -= zones[i-1].distance;
            
        for (int j = 1; j < speed_value_size; j++)
        {
            // X = V*t
            double t_cur = ((distance * 36.0) / (10.0 * (double)j));
            // set the current time it would take to traverse the distance
            zones[i].time_speed[j] = t_cur;
            if (i > 0)
            {
                // add the speed from the previous value
                double h = zones[i - 1].time_speed[j];
                t_cur += zones[i - 1].time_speed[j];
                zones[i].time_speed[j] = t_cur;
            }
            if (double(distance) / t_cur > v_max_ms)
            {
                zones[i].speeds.push_back(0);
                continue;
            }
            double r = t_cur / duration;
            if (t_cur < duration)
            {
                zones[i].speeds.push_back(j);
            }
            else if (is_within_green(t_cur, duration))
            {
                zones[i].speeds.push_back(j);
            }
            else
            {
                zones[i].speeds.push_back(0);
            }
        }
    }

    if (lightCount == 1)
    {
        // there is only 1 light so no need to sort things
        zones[0].speeds.sort();
        cout << zones[0].speeds.back() << endl;
    }
    else
    {
        // hand given sorting that should be automated
        std::list<double> v_test, v_temp;
        for (int i = 0; i < lightCount - 1; i++)
        {
            zones[i].speeds.sort();
            zones[i + 1].speeds.sort();
            if (i == 0)
            {
                set_intersection(zones[i].speeds.begin(), zones[i].speeds.end(),
                    zones[i + 1].speeds.begin(), zones[i + 1].speeds.end(), back_inserter(v_test));
            }
            else
            {
                set_intersection(zones[i + 1].speeds.begin(), zones[i + 1].speeds.end(),
                    v_test.begin(), v_test.end(), back_inserter(v_temp));
                v_test = v_temp;
                v_temp.clear();
            }
            v_test.sort();
        }
        cout << (int)v_test.back() << endl;   
    }
}