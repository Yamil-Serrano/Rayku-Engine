#include "Collectibles.hpp"

Collectibles::Collectibles(float pos_x, float pos_y, float width, float height, Color color) {
    rect = {pos_x, pos_y, width, height};
    this->color = color;
    isCollected = false;
}

void Collectibles::Draw() {
    if (isCollected) return; // Collected 
    DrawRectangleRec(rect, color);
}

Rectangle Collectibles::GetRect() {
    return rect;
}

bool Collectibles::IsCollected() {
    return isCollected;
}

void Collectibles::Collect() {
    isCollected = true;
}
