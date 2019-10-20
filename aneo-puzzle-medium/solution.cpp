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
        cerr << "Speed : " << v << " M: " << m << endl;
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
    
    float maxSpeed = speed / 3.6f;
    
    cerr << "Max speed (km/h): " << maxSpeed << endl;
    float time_elapsed = 0;
    float v_out = maxSpeed;
    
    for (int i = 0; i < lightCount; i++) {
        int distance;
        int duration;
        cin >> distance >> duration; cin.ignore();
        cerr << "Distance (meter) and duration(seconds): " 
            << distance << " " << duration << endl;
        
        float current_time = duration; //- time_elapsed;
        cerr << "elapsed time from the light: " << current_time << endl;
        
        float v_cur = calc_speed(distance, maxSpeed, current_time, duration);
        if (v_cur == maxSpeed)
        {
            cerr << " 2 " << endl;
            v_cur = calc_speed(distance, v_out, current_time, duration);    
        }
        else if (i > 0 && v_out != maxSpeed)
        {
            cerr << " 1 " << endl;
            float v_tmp = check_existing(v_out, distance, duration);
            if (v_tmp != -1)
            {
                v_cur = v_tmp;
                speed = v_cur;
            }
        }
        
        v_out = v_cur;
        cerr << "tmp output " << v_out << endl;
        time_elapsed += calculate_v(distance, v_cur);
    }
    cerr << "output speed (km/h): " << v_out*3.6f << endl;
    cout << (int)(v_out*3.6f) << endl;
}