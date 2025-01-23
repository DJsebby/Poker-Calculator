#ifndef W_ODDS_H
#define W_ODDS_H

#include "deck.h"
#include "handEvaluator.h"

class winningOdds {
 private:
  float oddsOfWinning;

 public:
  winningOdds() { oddsOfWinning = 0; }
  float getOddsOfWinning() { return oddsOfWinning; }
  // monte carlo simulator of odds of winning
  void SimProbabilityOfWinning(std::vector<cards> &hand,
                               std::vector<cards> &river,
                               std::vector<cards> &opHand, int numOfIter,
                               deck &d) {
    float wins = 0;
    float losses = 0;
    float tie = 0;

    handEvaluator a;

    for (size_t i = 0; i < numOfIter; i++) {
      if (a.evaluateHandStrength(hand, river) ==
          a.evaluateHandStrength(opHand, river))  // early return condition
      {
        tie++;
      } else if (a.evaluateHandStrength(hand, river) >
                 a.evaluateHandStrength(opHand, river)) {
        wins++;
      } else if (a.evaluateHandStrength(hand, river) <
                 a.evaluateHandStrength(opHand, river)) {
        losses++;
      }

      d.reshuffle(opHand, river);
      opHand.clear();
      opHand = d.drawHand();
      river.clear();
      river = d.drawRiver();
    }
    if ((wins + tie + losses) > 0) {
      oddsOfWinning = (wins + 0.5 * tie) / (wins + tie + losses);
    } else {
      oddsOfWinning = 0;  // Default case for no iterations
    }
  }
};

#endif