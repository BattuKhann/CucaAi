#include <iostream>
#include <bitset>
#include <string>
#include <ctime>
#include "Board.hpp" // Includes your new header
#include "Dice.hpp"

// Helper to print map details
void printDebugInfo(const Map* map) {
    if (!map) return;

    std::cout << "=== MAP LOADED SUCCESSFULLY ===\n";
    std::cout << "Territories: " << map->numTerritories << "\n";
    std::cout << "Continents:  " << map->numContinents << "\n\n";

    std::cout << "--- Adjacency Check (First 5 Territories) ---\n";
    for (int i = 0; i < std::min(5, map->numTerritories); i++) {
        // bitset<64> prints the binary representation of the integer
        std::cout << "ID " << i << " Connections: " 
                  << std::bitset<64>(map->adjacent[i]) << "\n";
    }

    std::cout << "\n--- Continent Check ---\n";
    for (int i = 0; i < map->numContinents; i++) {
        std::cout << "Continent " << i << " (Bonus " << map->bonuses[i] << "): " 
                  << std::bitset<64>(map->continents[i]) << "\n";
    }
    std::cout << "===============================\n";
}

int main() {
    // Path to your JSON file
    std::string path = "../../maps/classic.json";

    std::cout << "Loading map from: " << path << "...\n";

    // 1. Load the Map (Allocates memory on Heap)
    Map* riskMap = loadMapFromFile(path);

    if (riskMap) {
        // 2. Create a Board Instance (Allocates State on Stack)
        Board myBoard(riskMap);

        // 3. Verify Data
        printDebugInfo(riskMap);

        // 4. Test Cloning (Simulate MCTS Step)
        Board copyBoard = myBoard.clone();
        std::cout << "\nBoard cloned successfully. State size: " 
                  << sizeof(copyBoard.getState()) << " bytes.\n";

        // 5. Clean up
        delete riskMap;
    } else {
        std::cerr << "FAILED to load map. Check file path and JSON format.\n";
    }

    Xoshiro256 engine(static_cast<unsigned int>(std::time(nullptr)));
    //std::mt19937 engine(static_cast<unsigned int>(std::time(nullptr)));

    int totalSimulations = 1000000;
    int attackerWins = 0;
    long totalAttackerLosses = 0;

    // Setup Scenario: 4 Total Attackers vs 2 Total Defenders
    int totalAttackerTroops = 1700;
    int defenderTroops = 2000;

    std::cout << "Simulating " << totalSimulations << " battles..." << std::endl;
    std::cout << "Attacker (" << totalAttackerTroops << ") vs Defender (" << defenderTroops << ")" << std::endl;

    for (int i = 0; i < totalSimulations; ++i) {
        // IMPORTANT: We pass (totalAttackerTroops - 1) because 1 army must stay behind.
        // The function simulates the "active" armies fighting to the death.
        RollOutcome result = roll(totalAttackerTroops - 1, defenderTroops, engine);

        if (result.win) {
            attackerWins++;
        }

        totalAttackerLosses += result.aLoss;
    }

    double winRate = (double)attackerWins / totalSimulations * 100.0;
    double avgALoss = (double)totalAttackerLosses / totalSimulations;

    std::cout << "---------------------------------" << std::endl;
    std::cout << "Attacker Wins: " << attackerWins << std::endl;
    std::cout << "Win Rate: " << winRate << "%" << std::endl;
    std::cout << "Avg Attacker Losses: " << avgALoss << " (out of " << totalAttackerTroops << ")" << std::endl;

    return 0;
}