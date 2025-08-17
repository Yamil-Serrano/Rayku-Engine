#pragma once
#include "raylib.h"

class Player {
    private:
        Rectangle rect; // Entity position
        float speed;
        Color color;

        int health;

        // knockback variables
        bool isKnockback;
        float velocity_X;
        float knockbackTimer; 

        // gravity and jump variables
        float velocity_Y; 
        float gravity;
        float jumpForce;
        bool isJumping;
        bool isTouchingWallHorizontally;

    public:
        Player(float pos_x, float pos_y, float width, float height, float speed, Color color);
        void Update();
        void Draw();
        
        Rectangle GetRect();

        void Jump();
        void knockback(Rectangle enemyPosition);
        bool isFalling();

        Vector2 GetPosition();

        void SetPosition(float x, float y);
        void SetVelocityY(float velocity);
        void SetJumping(bool jumping);
        void SetTouchingWallHorizontally(bool touching);
};