#pragma once
#include "raylib.h"

class Collectibles {
    private:
    Rectangle rect;
    Color color;

    bool isCollected;
        
    public:
        Collectibles(float pos_x, float pos_y, float width, float height, Color color);
        void Draw();
        Rectangle GetRect();

        bool IsCollected();
        void Collect();
};

