# include "raylib.h"
#include "src/Player/Player.hpp"
#include "src/Enemy/Enemy.hpp"
#include "src/Blocks/Blocks.hpp"

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

    // Block initialization
    Blocks block(700, 380, 50, 50, GREEN);

    while (!WindowShouldClose()) {
        // Game logic update here
        player.Update();
        player.Draw();
        

        // -------------------- Collition system --------------------
        Rectangle playerRect = player.GetRect();
        Rectangle enemyRect = enemy.GetRect();
        Rectangle blockRect = block.GetRect();

        // When using a vector of enemies, use a for loop here.
        // Enemy collition system
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
        
        // Blocks collition system
        if (CheckCollisionRecs(playerRect, blockRect)) {
            // Calculate overlap distances for each direction
            float overlapLeft = (playerRect.x + playerRect.width) - blockRect.x;
            float overlapRight = (blockRect.x + blockRect.width) - playerRect.x;
            float overlapTop = (playerRect.y + playerRect.height) - blockRect.y;
            float overlapBottom = (blockRect.y + blockRect.height) - playerRect.y;
            
            // Find the smallest overlap to determine collision direction
            bool fromLeft = (overlapLeft < overlapRight) && (overlapLeft < overlapTop) && (overlapLeft < overlapBottom);
            bool fromRight = (overlapRight < overlapLeft) && (overlapRight < overlapTop) && (overlapRight < overlapBottom);
            bool fromTop = (overlapTop < overlapLeft) && (overlapTop < overlapRight) && (overlapTop < overlapBottom);
            bool fromBottom = (overlapBottom < overlapLeft) && (overlapBottom < overlapRight) && (overlapBottom < overlapTop);
            
            // Handle collision based on direction with small buffer for precision
            const float COLLISION_BUFFER = 0.1f; // Small buffer to prevent visual penetration
            
            if (fromTop && player.isFalling()) {
                // Player lands on top of block
                player.SetPosition(playerRect.x, blockRect.y - playerRect.height - COLLISION_BUFFER);
                player.SetVelocityY(0);
                player.SetJumping(false);
            }
            else if (fromBottom) {
                // Player hits block from below
                player.SetPosition(playerRect.x, blockRect.y + blockRect.height + COLLISION_BUFFER);
                player.SetVelocityY(0);
            }
            else if (fromLeft) {
                // Player hits block from the left
                player.SetPosition(blockRect.x - playerRect.width - COLLISION_BUFFER, playerRect.y);
            }
            else if (fromRight) {
                // Player hits block from the right
                player.SetPosition(blockRect.x + blockRect.width + COLLISION_BUFFER, playerRect.y);
            }
        }
        // ------------------------------------------------------------

        enemy.Update();
        enemy.Draw();

        block.Draw();
        
        // Draw here
        BeginDrawing();
            ClearBackground(RAYWHITE);
        
            EndDrawing();
    }

    // Free resources
    CloseWindow();

    return 0;
    
}