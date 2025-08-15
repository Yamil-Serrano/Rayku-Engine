#include "src/Map_Loader/Map_loader.hpp"
#include "Map_loader.hpp"

Map_loader::Map_loader() {}
Map_loader::~Map_loader() {}

void Map_loader::LoadCSVMap(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        // Cant read the CSV map
        return;
    }

    int pos_y = 0;
    string line;
    while (getline(file, line)) { // Reading the line
        int pos_x = 0;
        std::stringstream ss(line);
        std::string value;

        while (getline(ss, value, ',')) {
            if (value == "1") {
                MapBlocks.push_back(Blocks(pos_x * blockSize, pos_y * blockSize, blockSize, blockSize, GREEN));
                pos_x++;
            }
            else if (value == "0") {
                pos_x++;
            }

        }

        pos_y++; 
    }
}

void Map_loader::Draw_Map() {
    for (Blocks& block : MapBlocks) {
        block.Draw();
    }
}

vector<Blocks> Map_loader::GetMapBlocks() {
    return MapBlocks;
}
