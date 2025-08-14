#include "Enemy.hpp"

Enemy::Enemy(float pos_x, float pos_y, float width, float height, float speed, Color color) {
    rect = {pos_x, pos_y, width, height};
    this->speed = speed;
    this->color = color;

    direction = 1;
    startEntityTime = GetTime();
    isAlive = true;

    velocity_Y = 0;
    gravity = 0.5;
    isJumping = false;
    isTouchingWallHorizontally = false;
}

void Enemy::Update() {
    if (!isAlive) return; // Ded

    // -------------------- Simple left and right movement --------------------
    double currentGameTime = GetTime();
    if (currentGameTime - startEntityTime >= 5.0 || isTouchingWallHorizontally) {
        direction *= -1; // Change direction
        startEntityTime = GetTime(); // Reset the initial timer
    }

    // Entity movement
    rect.x += speed * direction;
    // -------------------------------------------------------------------------

     // Aplaying gravity
    velocity_Y += gravity;
    rect.y += velocity_Y;
}

void Enemy::Jump() {
    velocity_Y = -10.0f; // Fixed jump force without variable
    isJumping = true;
}

bool Enemy::isFalling() {
    return velocity_Y > 0;
}

void Enemy::TakeDamage() {
    isAlive = false;
}

bool Enemy::IsAlive() {
    return isAlive;
}

void Enemy::Draw() {
    if (!isAlive) return;
    DrawRectangleRec(rect, color);
}

Rectangle Enemy::GetRect() {
    return rect;
}

void Enemy::SetPosition(float x, float y) {
    rect.x = x;
    rect.y = y;
}

void Enemy::SetVelocityY(float velocity) {
    velocity_Y = velocity;
}

void Enemy::SetJumping(bool jumping) {
    isJumping = jumping;
}

void Enemy::SetTouchingWallHorizontally(bool touching) {
    isTouchingWallHorizontally = touching;
}