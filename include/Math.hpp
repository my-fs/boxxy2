#pragma once

#include <iostream>

struct Vector2f {
    Vector2f(float p_x, float p_y)
    :x(p_x), y(p_y){}
    
    void print() {
        std::cout << x << ", " << y << std::endl;
    }

    float x, y;
};

struct Vector2int {
    Vector2int(int p_x, int p_y)
    :x(p_x), y(p_y){}

    int x, y;
};
