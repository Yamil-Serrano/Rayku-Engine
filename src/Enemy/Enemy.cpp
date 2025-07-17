#include "Enemy.hpp"

Enemy :: Enemy(float pos_x, float pos_y, float width, float height, float speed, Color color) {
    rect = {pos_x, pos_y, width, height};
    this->speed = speed;
    this->color = color;

    direction = 1;
    startEntityTime = GetTime(); // Initial time of the entity
    isAlive = true;

    // Initializing Gravity and jump variables
    velocity_Y = 0;
    gravity = 0.5;
    jumpForce = -10.0f; 
}

void Enemy :: Update() {
    if (!isAlive) return; // Ded

    // -------------------- Simple left and right movement --------------------
    double currentGameTime = GetTime();
    if (currentGameTime - startEntityTime >= 2.0) {
        direction *= -1; // Change direction
        startEntityTime = GetTime(); // Reset the initial timer
    }

    // Entity movement
    rect.x += speed * direction;
    // -------------------------------------------------------------------------

     // Aplaying gravity
    velocity_Y += gravity;
    rect.y += velocity_Y;
    

    // Floor detection
    if (rect.y >= 400) {
        rect.y = 400;
        velocity_Y = 0;
        isJumping = false;
    }
}

void Enemy::Jump() {
    velocity_Y = jumpForce;
    isJumping = true;
}

void Enemy::TakeDamage() {
    isAlive = false;
}

bool Enemy::IsAlive() {
    return isAlive;
}

void Enemy::Draw() {
    if (!isAlive) return; // Ded
    DrawRectangleRec(rect, color);
}

Rectangle Enemy::GetRect() {
    return rect;
}
