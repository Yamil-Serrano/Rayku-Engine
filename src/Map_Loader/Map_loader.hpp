#pragma once
#include "raylib.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "src/Blocks/Blocks.hpp"
#include "src/Collectibles/Collectibles.hpp"

using namespace std;

class Map_loader {
    private:
        int mapGridSize = 50;

        int blockSize = 50;
        vector<Blocks> MapBlocks;

        int collectiblesSize = 25;
        vector<Collectibles> MapCollectibles;
        
    public:
        Map_loader();
        ~Map_loader();

        void LoadCSVMap(const string& filename);
        void Draw_Map();

        vector<Blocks>& GetMapBlocks();
        vector<Collectibles>& GetMapCollectibles();
};
