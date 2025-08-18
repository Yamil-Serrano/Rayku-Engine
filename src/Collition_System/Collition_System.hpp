#pragma once
#include "raylib.h"
#include "src/Player/Player.hpp"
#include "src/Enemy/Enemy.hpp"
#include "src/Blocks/Blocks.hpp"
#include "src/Collectibles/Collectibles.hpp"
#include "src/Audio_Manager/Audio_Manager.hpp"
#include <vector>
#include <cmath> 

using namespace std;

class Collition_System {
    private:
        Player& player;
        vector <Enemy>& enemies;
        vector <Blocks>& blocks;
        vector <Collectibles>& collectibles;
        AudioManager& audio;
        
    public:
        Collition_System(Player& player, std::vector<Enemy>& enemies, vector<Blocks>& blocks, vector<Collectibles>& collectibles, AudioManager& audioManager);
        void CheckPlayerCollitions();
        void CheckEnemyCollitions();
};
