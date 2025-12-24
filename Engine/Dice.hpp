#pragma once
#include <random>
#include <cstdint>
#include <climits>

const uint32_t TOTAL_WEIGHT_3v2 = 7776;
const uint32_t THRESHOLD_A_LOSE_2 = 2275;
const uint32_t THRESHOLD_BOTH_LOSE_1 = 2275 + 2611;

static const int A_LOSS_LOOKUP[3] = {2, 1, 0};
static const int D_LOSS_LOOKUP[3] = {0, 1, 2};

struct Xoshiro256 {
    uint64_t s[4];

    static inline uint64_t rotl(const uint64_t x, int k) {
        return (x << k) | (x >> (64 - k));
    }

    Xoshiro256(uint64_t seed) {
        uint64_t z = seed;
        for (int i = 0; i < 4; ++i) {
            z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
            z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
            s[i] = z ^ (z >> 31);
        }
    }

    inline uint64_t next() {
        const uint64_t result = rotl(s[1] * 5, 7) * 9;
        const uint64_t t = s[1] << 17;

        s[2] ^= s[0];
        s[3] ^= s[1];
        s[1] ^= s[2];
        s[0] ^= s[3];

        s[2] ^= t;
        s[3] = rotl(s[3], 45);

        return result;
    }
    
    inline uint32_t next_bounded(uint32_t range) {
        uint32_t x = (uint32_t)(next() >> 32);
        uint64_t m = (uint64_t)x * (uint64_t)range;
        return (uint32_t)(m >> 32);
    }
};

struct RollOutcome{
    bool win;
    int aLoss;
    int dLoss;
};

struct RollWeights{
    int aLoss;
    int equalLoss;
    int dLoss;
};

inline RollWeights ProbabilityTable[3][2] = {{{21, 0, 15}, {161, 0, 55}}, 
                                      {{91, 0, 125}, {581, 420, 295}}, 
                                      {{441, 0, 855}, {2275, 2611, 2890}}};

RollOutcome roll(int attackerCount, int defenderCount, Xoshiro256& engine);