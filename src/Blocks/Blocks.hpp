#pragma once
#include "raylib.h"

class Blocks {
    private:
    Rectangle rect;
    Color color;
        
    public:
        Blocks(float pos_x, float pos_y, float width, float height, Color color);
        void Draw();
        Rectangle GetRect();
};

