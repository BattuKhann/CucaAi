#include <cstdint>

const int NUM_TERRITORIES = 42;

struct Territory{

};

struct Board{

};

struct Map{
    uint64_t territories[NUM_TERRITORIES];

    uint8_t owners[NUM_TERRITORIES];
    uint16_t armies[NUM_TERRITORIES];

    Map(){

    }
};  