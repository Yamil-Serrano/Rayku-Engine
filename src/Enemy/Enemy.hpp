#pragma once
#include "raylib.h"

class Enemy {
    private:
        Rectangle rect;
        float speed;
        Color color;

        int direction;
        double startEntityTime;
        bool isAlive;

         // gravity and jump variables
        float velocity_Y; 
        float gravity;
        float jumpForce;
        bool isJumping;

    public:
        Enemy(float pos_x, float pos_y, float width, float height, float speed, Color color);
        void Update();
        void Draw();

        Rectangle GetRect();

        void Jump();
        void TakeDamage();
        bool IsAlive();
        
};
