#pragma once
#include "raylib.h"
#include "src/Player/Player.hpp"
#include "src/Enemy/Enemy.hpp"
#include "src/Blocks/Blocks.hpp"
#include <vector>
#include <cmath> 

using namespace std;

class Collition_System {
    private:
        Player& player;
        vector <Enemy>& enemies;
        vector <Blocks>& blocks;
        
    public:
        Collition_System(Player& player, std::vector<Enemy>& enemies, std::vector<Blocks>& blocks);
        void CheckCollisions();
};
