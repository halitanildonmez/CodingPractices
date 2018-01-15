#include <iostream>

int main()
{
    while (1) {
        int index = -1;
        int value = -1;
        for (int i = 0; i < 8; i++) {
            int mountainH;
            std::cin >> mountainH; std::cin.ignore();
            if (mountainH >= value) {
                value = mountainH;
                index = i;
            }
        }
        std::cout << index << std::endl;
    }
}