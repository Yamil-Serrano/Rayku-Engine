#pragma once
#include "raylib.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "src/Blocks/Blocks.hpp"

using namespace std;

class Map_loader {
    private:
        int blockSize = 50;
        vector<Blocks> MapBlocks;
        
    public:
        Map_loader();
        ~Map_loader();

        void LoadCSVMap(const string& filename);
        void Draw_Map();
         vector<Blocks> GetMapBlocks();
};
