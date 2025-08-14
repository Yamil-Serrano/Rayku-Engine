#include "raylib.h"

#include "src/Player/Player.hpp"
#include "src/Enemy/Enemy.hpp"
#include "src/Blocks/Blocks.hpp"
#include "src/Collition_System/Collition_System.hpp"

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
    Player player(600.0f, screenHeight/2, 50, 50, 5, BLUE);

    vector<Enemy> enemies = {
        Enemy(150.0f, screenHeight/2, 50, 50, 2, RED)
    };

    // Block initialization
    vector<Blocks> blocks = {
        // Right wall
        Blocks(700, 360, 50, 50, GREEN),
        Blocks(700, 310, 50, 50, GREEN), 
        Blocks(700, 260, 50, 50, GREEN),
        Blocks(700, 210, 50, 50, GREEN), 

        // Floor
        Blocks(650, 360, 50, 50, GREEN),
        Blocks(600, 360, 50, 50, GREEN),
        Blocks(550, 360, 50, 50, GREEN),
        Blocks(500, 360, 50, 50, GREEN),
        Blocks(450, 360, 50, 50, GREEN),
        Blocks(400, 360, 50, 50, GREEN),
        Blocks(350, 360, 50, 50, GREEN),
        Blocks(300, 360, 50, 50, GREEN),
        Blocks(250, 360, 50, 50, GREEN),
        Blocks(200, 360, 50, 50, GREEN),
        Blocks(150, 360, 50, 50, GREEN),
        Blocks(100, 360, 50, 50, GREEN),
        Blocks(50, 360, 50, 50, GREEN),

        // Left wall
        Blocks(50, 360, 50, 50, GREEN),
        Blocks(50, 310, 50, 50, GREEN), 
        Blocks(50, 260, 50, 50, GREEN),
        Blocks(50, 210, 50, 50, GREEN), 
    };

    // Collition System  initialization
    Collition_System collisionSystem(player, enemies, blocks);
    
    while (!WindowShouldClose()) {
        // Game logic update here
        player.Update();

        for(Enemy& enemy : enemies) {
            enemy.Update();
        }


        // -------------------- Collition system --------------------
        collisionSystem.CheckPlayerCollitions();
        collisionSystem.CheckEnemyCollitions();
        // ------------------------------------------------------------

        // Render everything
        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            // Draw all our game objects
            player.Draw();
            for(Enemy& enemy : enemies) {
                enemy.Draw();
            }
            
            for (Blocks& block : blocks) {
                block.Draw();
            }
            
        EndDrawing();
    }

    // Free resources
    CloseWindow();

    return 0;
    
}

