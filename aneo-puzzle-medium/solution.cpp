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
float calculate_v (float x, float t) 
{
    return x/t;
}
// meters to kilometers(km)
float m2km(float distance) 
{
    return distance/1000;
}
// seconds to hours
float s2h(float seconds) 
{
    return seconds / 3600;
}
int main()
{
    int speed;
    cin >> speed; cin.ignore();
    int lightCount;
    cin >> lightCount; cin.ignore();
    
    cerr << "Max speed (km/h): " << speed << endl;
    float time_elapsed = 0;
    int v_out = speed;
    
    for (int i = 0; i < lightCount; i++) {
        int distance;
        int duration;
        cin >> distance >> duration; cin.ignore();
        cerr << "Distance (meter) and duration(seconds): " 
            << distance << " " << duration << endl;
        
        // Conver to km from meter
        float km_dist = m2km(distance);
        float h_dur = s2h(duration);
        cerr << "KM distance: " << km_dist << " Hour duration: " <<
            h_dur << "\n";
        
        float current_time = h_dur - time_elapsed;
        cerr << "elapsed time from the light: " << current_time << endl;
        
        float v_cur = calculate_v(km_dist, current_time);
        cerr << "Current calculated speed: " << v_cur << endl;
        // we can use the max speed
        if (v_cur < speed)
            v_cur = speed;
        else{
            cerr << "Speed is not enough" << endl;
            float new_time = calculate_v(km_dist, speed);
            if (new_time > h_dur)
            {
                float new_speed = calculate_v(km_dist, 2*current_time);
                cerr << "max speed is too slow " << new_time << endl;
                if (new_time <= speed)
                    v_cur = new_speed;
            }
        }
            
        v_out = v_cur;
    }
    cerr << "output speed (km/h): " << v_out << endl;
    cout << (int)v_out << endl;
}