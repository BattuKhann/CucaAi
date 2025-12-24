#include "Dice.hpp"
#include <algorithm>

RollOutcome roll(int attackerCount, int defenderCount, Xoshiro256& engine){ //ensure attackercount is reduced by 1 before calling
    RollOutcome outcome = {false, 0, 0};

    int aLoss = 0;
    int dLoss = 0;

    while (attackerCount >= 3 && defenderCount >= 2) {
        uint32_t r = engine.next_bounded(TOTAL_WEIGHT_3v2);
        //uint32_t r = engine() % TOTAL_WEIGHT_3v2;

        uint32_t idx = (r >= THRESHOLD_A_LOSE_2) + (r >= THRESHOLD_BOTH_LOSE_1);

        int al = A_LOSS_LOOKUP[idx];
        int dl = D_LOSS_LOOKUP[idx];

        aLoss += al;
        attackerCount -= al;
        dLoss += dl;
        defenderCount -= dl;
    }

    while(attackerCount > 0 && defenderCount > 0){
        int aDice = std::min(attackerCount, 3);
        int dDice = std::min(defenderCount, 2);

        RollWeights* w = &ProbabilityTable[aDice - 1][dDice - 1];

        uint32_t r = engine.next_bounded(w->aLoss + w->equalLoss + w->dLoss);
        //uint32_t r = engine() % (w->aLoss + w->equalLoss + w->dLoss);

        if(r < w->aLoss){
            aLoss += std::min(aDice, dDice);
            attackerCount -= std::min(aDice, dDice);
        } else if(r < (w->aLoss + w->equalLoss)){
            aLoss += 1; attackerCount -= 1;
            dLoss += 1; defenderCount -= 1;
        } else {
            int loss = std::min(aDice, dDice);
            dLoss += loss;
            defenderCount -= loss;
        }
    }

    outcome.win = attackerCount > 0;
    outcome.aLoss = aLoss;
    outcome.dLoss = dLoss;
    return outcome;
}