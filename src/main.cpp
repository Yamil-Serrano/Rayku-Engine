#include "raylib.h"

#include "src/Player/Player.hpp"
#include "src/Enemy/Enemy.hpp"
#include "src/Blocks/Blocks.hpp"
#include "src/Collition_System/Collition_System.hpp"
#include "src/Map_Loader/Map_loader.hpp"

#include <cmath> 
#include <vector>

using namespace std;

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Rayku Engine");

    Image icon = LoadImage("src/assets/settings.png");
    SetWindowIcon(icon);
    UnloadImage(icon);

    SetTargetFPS(60);

    // Map Loader
    Map_loader Maploader;
    Maploader.LoadCSVMap("src/Maps/map0.csv");

    // Player initialization
    Player player(600.0f, screenHeight/2, 50, 50, 5, BLUE);

    // Enemies initialization
    vector<Enemy> enemies = {
        Enemy(150.0f, screenHeight/2, 50, 50, 2, RED)
    };

    // Blocks initialization
    vector <Blocks> blocks = Maploader.GetMapBlocks();

    // Collition System initialization
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
            
            Maploader.Draw_Map();
            
        EndDrawing();
    }

    // Free resources
    CloseWindow();

    return 0;
    
}

