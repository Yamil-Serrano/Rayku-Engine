#include "Blocks.hpp"

Blocks::Blocks(float pos_x, float pos_y, float width, float height, Color color) {
    rect = {pos_x, pos_y, width, height};
    this->color = color;
}

void Blocks::Draw() {
    DrawRectangleRec(rect, color);
}

Rectangle Blocks::GetRect() {
    return rect;
}