#pragma once
#include "raylib.h"

class Enemy {
    private:
        Rectangle rect;
        float speed;
        Color color;

        // gravity and jump variables
        float velocity_Y; 
        float gravity;
        bool isJumping;
        bool isTouchingWallHorizontally;

        int direction;
        double startEntityTime;
        bool isAlive;

    public:
        Enemy(float pos_x, float pos_y, float width, float height, float speed, Color color);
        void Update();
        void Draw();
        
        Rectangle GetRect();

        void Jump();
        bool isFalling();
        void TakeDamage();
        bool IsAlive();

        void SetPosition(float x, float y);
        void SetVelocityY(float velocity);
        void SetJumping(bool jumping);
        void SetTouchingWallHorizontally(bool touching);
};