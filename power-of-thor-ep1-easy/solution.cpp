#include <iostream>
#include <string>

int main()
{
    int lightX; // the X position of the light of power
    int lightY; // the Y position of the light of power
    int initialTX; // Thor's starting X position
    int initialTY; // Thor's starting Y position
    std::cin >> lightX >> lightY >> initialTX >> initialTY; std::cin.ignore();

    // game loop
    while (1) {
        int remainingTurns; // The remaining amount of turns Thor can move. Do not remove this line.
        std::cin >> remainingTurns; std::cin.ignore();
        
        int xDir = lightX - initialTX;
        int yDir = lightY - initialTY;
        
        std::string output = "";

        if (xDir == 0) {
            if (yDir < 0) {
                output = "N";
                initialTY--;
            } else {
                output = "S";
                initialTY++;
            }
        } else if (yDir == 0) {
            if (xDir < 0) {
                output = "W";
                initialTX--;
            } else {
                output = "E";
                initialTX++;
            }
        } else {
            if (xDir > 0 && yDir > 0) {
                output = "SE";
                initialTY++;
                initialTX++;
            } else if (xDir < 0 && yDir < 0) {
                output = "NW";
                initialTY--;
                initialTX--;
            } else if (xDir < 0 && yDir > 0) {
                output = "SW";
                initialTY++;
                initialTX--;
            } else if (xDir > 0 && yDir < 0) {
                output = "NE";
                initialTY--;
                initialTX++;
            }
        }

        std::cout << output << std::endl;
    }
}