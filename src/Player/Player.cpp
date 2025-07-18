#include "Player.hpp"

Player :: Player(float pos_x, float pos_y, float width, float height, float speed, Color color) {
    rect = {pos_x, pos_y, width, height};
    this->speed = speed;
    this->color = color;
    health = 3;
    isKnockback = false;

    // Initializing Gravity and jump variables
    velocity_Y = 0;
    velocity_X = 0;
    gravity = 0.5;
    jumpForce = -10.0f; 
    isTouchingWallHorizontally = false;
}

void Player :: Update() {

    if (isKnockback) {
        knockbackTimer -= GetFrameTime();

        // Appliying horizontal knockback
        rect.x += velocity_X * GetFrameTime() * 60; // Normalized to 60 FPS

        if (knockbackTimer <= 0) {
            isKnockback = false;
        }
    }

    // Allow movement if not knockback
    if (!isKnockback) {
        // Note if I delete the boolean "isTouchingWall" i will be able to climb the walls
        if (IsKeyDown(KEY_RIGHT) && !isTouchingWallHorizontally) rect.x += speed;
        if (IsKeyDown(KEY_LEFT)  && !isTouchingWallHorizontally) rect.x -= speed;
    }

    // Aplaying gravity
    velocity_Y += gravity;
    rect.y += velocity_Y;
    

    // Floor detection
    if (rect.y >= 400) {
        rect.y = 400;
        velocity_Y = 0;
        isJumping = false;
    }

    // Allow jump if not knockback and not against a wall
    if (IsKeyPressed(KEY_SPACE) && !isKnockback && !isJumping) {
    Jump();
}

}

void Player::Jump() {
    velocity_Y = jumpForce;
    isJumping = true;
}

void Player::knockback(Rectangle enemyPosition) {
    isKnockback = true;
    knockbackTimer = 0.65f;

    Jump();
    // knockback horizontal force
    velocity_X = (this->rect.x > enemyPosition.x) ? 5.5f : -5.5f;
}

bool Player::isFalling() {
    if (velocity_Y > 0 ) {
        return true;
    }

    else {
        return false;
    }
}

void Player::Draw() {
    DrawRectangleRec(rect, color);
}

Rectangle Player::GetRect() {
    return rect;
}

void Player::SetPosition(float x, float y) {
    rect.x = x;
    rect.y = y;
}

void Player::SetVelocityY(float velocity) {
    velocity_Y = velocity;
}

void Player::SetJumping(bool jumping) {
    isJumping = jumping;
}

void Player::SetTouchingWallHorizontally(bool touching) {
    isTouchingWallHorizontally = touching;
}
