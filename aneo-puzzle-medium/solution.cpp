#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

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
// meters to kilometers
float m2km(float distance) 
{
    return distance/1000;
}
float msTokmh(float speed) 
{
    return speed * 3.6f;
}
// seconds to hours
float s2h(float seconds) 
{
    return seconds / 3600;
}
float check_existing(float speed, float dist, float duration)
{
    float t = calculate_v(dist, speed);
    if (t < duration)
        return speed;
    float t_x = t / duration;
    if (fmod(t_x, 2) == 0)
        return speed;
    return -1.0f;
}
float calc_speed(float dist, float vmax, float elapsed, float duration) 
{
    float v = calculate_v(dist, elapsed);
    if (v <= vmax) {
        cerr << "max speed is enough" << endl;
        return vmax;
    }
    int m = 2;
    while (v > vmax)
    {
        v = calculate_v(dist, elapsed * m);
        cerr << "Speed : " << v << endl;
        m += 2;
    }
    return v;
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
        
        float v_cur = calc_speed(km_dist, speed, current_time, h_dur);
        
        if (i > 0 && v_out != speed)
        {
            float v_tmp = check_existing(v_out, km_dist, h_dur);
            if (v_tmp != -1)
                v_cur = v_tmp;
        }
        else 
        {
            v_cur = calc_speed(km_dist, speed, current_time, h_dur);    
        }
        
       
        
        v_out = v_cur;
        time_elapsed += calculate_v(km_dist, v_cur);
    }
    cerr << "output speed (km/h): " << v_out << endl;
    cout << (int)v_out << endl;
}