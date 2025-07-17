# include "raylib.h"
#include "src/Player/Player.hpp"
#include "src/Enemy/Enemy.hpp"

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib prototype");

    SetTargetFPS(60);

    // Player initialization
    Player player(screenWidth/2, screenHeight/2, 50, 50, 5, BLUE);

    // Enemy initialization
    Enemy enemy(20.0f, screenHeight/3, 50, 50, 2, RED);

    while (!WindowShouldClose()) {
        // Game logic update here
        player.Update();
        player.Draw();
        

        // -------------------- Collition system --------------------
        Rectangle playerRect = player.GetRect();
        Rectangle enemyRect = enemy.GetRect();

        // When using a vector of enemies, use a for loop here.

        if (enemy.IsAlive()) {
            if (CheckCollisionRecs(playerRect, enemyRect)) {
                // Verify if the player is falling over the enemy (stomping)
                bool isStomping = (playerRect.y + playerRect.height < enemyRect.y + 20) && (player.isFalling());

                if (isStomping) {
                    // Stomping effect
                    player.Jump();
                    enemy.TakeDamage();
                } 
                else {
                    // lateral collition
                    player.knockback(enemyRect);
                }
            }
        }
        // ------------------------------------------------------------

        enemy.Update();
        enemy.Draw();
        
        // Draw here
        BeginDrawing();
            ClearBackground(RAYWHITE);
        
            EndDrawing();
    }

    // Free resources
    CloseWindow();

    return 0;
    
}