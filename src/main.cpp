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
    Blocks block(700, 360, 50, 50, GREEN);

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
            // Calculate overlap distances for all 4 directions
            float overlaps[4] = {
                (playerRect.x + playerRect.width) - blockRect.x,    // ← Left penetration
                (blockRect.x + blockRect.width) - playerRect.x,    // → Right penetration
                (playerRect.y + playerRect.height) - blockRect.y,  // ↑ Top penetration
                (blockRect.y + blockRect.height) - playerRect.y    // ↓ Bottom penetration
            };

            /* 
            Find which side has the smallest overlap.
            Why? The smallest overlap indicates:
            - The direction where collision is most "shallow" (least penetration)
            - The most natural correction direction (avoids over-correction)
            - The actual side where contact is happening
            */
            int minIndex = 0; // Start with left side (index 0)
            for (int i = 1; i < 4; i++) {
                if (overlaps[i] < overlaps[minIndex]) minIndex = i; // New smallest overlap found
            }

            const float BUFFER = 0.1f; // Small gap to prevent visual clipping

            // Resolve collision based on direction
            switch (minIndex) {
                case 0: // ← Left collision
                    player.SetPosition(blockRect.x - playerRect.width - BUFFER, playerRect.y);
                    break;
                    
                case 1: // → Right collision
                    player.SetPosition(blockRect.x + blockRect.width + BUFFER, playerRect.y);
                    break;
                    
                case 2: // ↑ Top collision (player landing)
                    if (player.isFalling()) {
                        player.SetPosition(playerRect.x, blockRect.y - playerRect.height - BUFFER);
                        player.SetVelocityY(0);
                        player.SetJumping(false);
                    }
                    break;
                    
                case 3: // ↓ Bottom collision (player head bump)
                    player.SetPosition(playerRect.x, blockRect.y + blockRect.height + BUFFER);
                    player.SetVelocityY(0);
                    break;
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