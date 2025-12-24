#pragma once

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

const int MAX_TERRITORIES = 64;

struct MapState {
    uint16_t armies[MAX_TERRITORIES];
    uint8_t owners[MAX_TERRITORIES];
    uint8_t currState; // 2 MSB for Phase, 3 LSB for Player

    MapState() {
        std::memset(this, 0, sizeof(MapState));
        currState = 1;
    }
};

struct Map {
    uint64_t* adjacent;
    uint64_t* continents;
    int* bonuses;

    int numTerritories;
    int numContinents;

    Map(int t_count, int c_count);

    ~Map();
};

class Board {
private:
    const Map* gameMap;
    MapState state;

public:
    Board(const Map* map_ptr) : gameMap(map_ptr) {}

    Board clone() const {
        return *this;
    }

    const MapState& getState() const { return state; }
    
};

Map* loadMapFromFile(const std::string& filename);