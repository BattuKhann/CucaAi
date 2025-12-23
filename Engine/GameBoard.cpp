#include <cstdint>
#include <string>
#include <vector>
#include <fstream>
#include "json.hpp"

const int NUM_TERRITORIES = 42;
const int NUM_CONTINENTS = 6;

struct Territory{
    std::string name;
    int ownerID;
    int troopCount;
    std::vector<Territory*> connections;
};

struct Continent{
    std::string name;
    int bonus;
    std::vector<Territory*> territories;
};

struct Map{
    Territory* territories; 
    Continent* continents;

    int numTerritories;
    int numContinents;

    Map(int t_count, int c_count) {
        numTerritories = t_count;
        numContinents = c_count;

        territories = new Territory[numTerritories];
        continents = new Continent[numContinents];
    }

    ~Map() {
        delete[] territories;
        delete[] continents;
    }
};

class Board{
    private:
        Map* gameMap;

    public:
        Board(const std::string& filename){
            gameMap = nullptr;
            loadMap(filename);
        }

        ~Board() {
            delete gameMap;
        }

        bool changeMap(const std::string& filename){
            delete gameMap;
            gameMap = nullptr;
            loadMap(filename);
        }

        bool loadMap(const std::string& filename){
            std::ifstream f(filename);
            if (!f.is_open()) return false;
            
            nlohmann::json data;
            try {
                f >> data;  
            } catch (const nlohmann::json::parse_error& e) {
                return false;
            }

            int t_count = 0;
            int c_count = 0;

            if (data.contains("configuration")) {
                t_count = data["configuration"].value("num_territories", 0);
                c_count = data["configuration"].value("num_continents", 0);
            }

            if (t_count == 0 || c_count == 0) return false;

            gameMap = new Map(t_count, c_count);

            for (const auto& t_json : data["territories"]) {
                int id = t_json.value("id", -1);
                    
                gameMap->territories[id].name = t_json.value("name", "Unknown");
                gameMap->territories[id].ownerID = 0;   
                gameMap->territories[id].troopCount = 0; 

                for (int neighborID : t_json["neighbors"]) {
                    if (neighborID >= 0 && neighborID < NUM_TERRITORIES) {
                        gameMap->territories[id].connections.push_back(&gameMap->territories[neighborID]);
                    }
                }
            }
            
            int i = 0;
            for (const auto& c_json : data["continents"]) {

                gameMap->territories[i].name = c_json.value("name", "Unknown");
                gameMap->territories[i].ownerID = 0;   
                gameMap->territories[i].troopCount = 0; 

                for (int tid : c_json["territory_ids"]) {
                    if (tid >= 0 && tid < NUM_TERRITORIES) {
                        gameMap->continents[i].territories.push_back(&gameMap->territories[tid]);
                    }
                }

                i++;
            }

            return true;
        }
};

struct MapStatus{
    uint64_t adjacent[NUM_TERRITORIES];
    uint64_t continents[10]; //flag if territory in continent (take outside of this struct)
    int bonuses[10];

    uint16_t armies[NUM_TERRITORIES];
    uint8_t owners[NUM_TERRITORIES];
    

    MapStatus(){

    }
};