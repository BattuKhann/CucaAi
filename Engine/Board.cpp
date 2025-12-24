#include "Board.hpp"
#include <fstream>
#include <iostream>
#include "json.hpp"

const int MAX_TERRITORIES = 64;

Map::Map(int t_count, int c_count) {
    numTerritories = t_count;
    numContinents = c_count;

    adjacent = new uint64_t[numTerritories]();
    continents = new uint64_t[numContinents]();
    bonuses = new int[numContinents]();
}

Map::~Map() {
    delete[] adjacent;
    delete[] continents;
    delete[] bonuses;
}

Map* loadMapFromFile(const std::string& filename){
    std::ifstream f(filename);
    if (!f.is_open()) return nullptr;
    
    nlohmann::json data;
    try {
        f >> data;  
    } catch (const nlohmann::json::parse_error& e) {
        return nullptr;
    }

    int t_count = data.value("configuration", nlohmann::json::object()).value("num_territories", 0);
    int c_count = data.value("configuration", nlohmann::json::object()).value("num_continents", 0);

    if (t_count <= 0 || t_count > MAX_TERRITORIES || c_count <= 0) {
        //std::cerr << "Error: Invalid map size or exceeds MAX_TERRITORIES (64)\n";
        return nullptr;
    }

    Map* gameMap = new Map(t_count, c_count);

    for (const auto& t_json : data["territories"]) {
        int id = t_json.value("id", -1);
        for (int neighborID : t_json["neighbors"]) {
            if (neighborID >= 0 && neighborID < gameMap->numTerritories) {
                gameMap->adjacent[id] |= (1ULL << neighborID);
                gameMap->adjacent[neighborID] |= (1ULL << id);
            }
        }
    }
    
    int i = 0;
    for (const auto& c_json : data["continents"]) {
        for (int tid : c_json["territory_ids"]) {
            if (tid >= 0 && tid < gameMap->numTerritories) {
                gameMap->continents[i] |= (1ULL << tid);
            }
        }

        gameMap->bonuses[i] = c_json.value("bonus", 0);

        i++;
    }

    return gameMap;
}