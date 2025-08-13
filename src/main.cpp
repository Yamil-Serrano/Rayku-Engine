#include "raylib.h"

#include "src/Player/Player.hpp"
#include "src/Enemy/Enemy.hpp"
#include "src/Blocks/Blocks.hpp"

#include <cmath> 
#include <vector>

using namespace std;

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
    vector<Blocks> blocks = {
        Blocks(700, 360, 50, 50, GREEN),
        Blocks(700, 310, 50, 50, GREEN), 
        Blocks(700, 260, 50, 50, GREEN),
        Blocks(700, 210, 50, 50, GREEN), 

        Blocks(650, 360, 50, 50, GREEN),
        Blocks(600, 360, 50, 50, GREEN),
        Blocks(550, 360, 50, 50, GREEN)
    };
    
    while (!WindowShouldClose()) {
        // Game logic update here
        player.Update();
        enemy.Update();


        // -------------------- Collition system --------------------
        Rectangle playerRect = player.GetRect();
        Rectangle enemyRect = enemy.GetRect();

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
        // Reset wall state for this frame
        player.SetTouchingWallHorizontally(false);

        for (Blocks block : blocks) {
            Rectangle blockRect = block.GetRect();
            Rectangle playerRect = player.GetRect();
            
            if (CheckCollisionRecs(playerRect, blockRect)) {
                // Find the center points to determine collision direction
                // Player center point
                float playerCenterX = playerRect.x + playerRect.width / 2;
                float playerCenterY = playerRect.y + playerRect.height / 2;

                // Block center point
                float blockCenterX = blockRect.x + blockRect.width / 2;
                float blockCenterY = blockRect.y + blockRect.height / 2;
                
                // Calculate distance between centers
                float deltaX = playerCenterX - blockCenterX;
                float deltaY = playerCenterY - blockCenterY;
                
                // The bigger difference tells us which side we hit
                float horizontalBias = 1.1f; 
                // With this bias we priorize the horizontal collition. 
                // Because sometimes the comparation bellow can be equal (5 = 5) 
                // so it will be detected as vertical collition instead horizontal. 
                
                if ( (abs(deltaX) * horizontalBias) > abs(deltaY)) {
                    // Horizontal collision - we hit the left or right side
                    if (deltaX > 0) {
                        // Player is to the right, push them further right
                        player.SetPosition(blockRect.x + blockRect.width, playerRect.y);
                    } else {
                        // Player is to the left, push them further left
                        player.SetPosition(blockRect.x - playerRect.width, playerRect.y);
                    }
                    player.SetTouchingWallHorizontally(true);
                } else {
                    // Vertical collision - we hit the top or bottom
                    if (deltaY > 0) {
                        // Player is below block - bonk! (head bump)
                        player.SetPosition(playerRect.x, blockRect.y + blockRect.height);
                        player.SetVelocityY(0);
                    } else {
                        // Player is above block - landing platform
                        // Only snap to platform if we're actually falling down
                        if (player.isFalling()) {
                            player.SetPosition(playerRect.x, blockRect.y - playerRect.height);
                            player.SetVelocityY(0);
                            player.SetJumping(false);
                        }
                    }
                }
            }
        }
        // ------------------------------------------------------------

        // Render everything
        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            // Draw all our game objects
            player.Draw();
            enemy.Draw();
            
            for (Blocks block : blocks) {
                block.Draw();
            }
            
        EndDrawing();
    }

    // Free resources
    CloseWindow();

    return 0;
    
}