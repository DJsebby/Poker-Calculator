#ifndef W_ODDS_H
#define W_ODDS_H

#include "deck.h"
#include "handEvaluator.h"

class winningOdds {
 private:
  int oddsOfWinning;

 public:
  winningOdds() { oddsOfWinning = 0; }
  int getOddsOfWinning() { return oddsOfWinning; }
  // monte carlo simulator of odds of winning
  int SimProbabilityOfWinning(std::vector<cards> &hand,
                              std::vector<cards> &river,
                              std::vector<cards> &opHand, int numOfIter,
                              deck &d) {
    int wins = 0;
    int losses = 0;
    int tie = 0;

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
    if (losses == 0) {
      return wins;
    }

    return (wins / losses);
  }
  ~winningOdds();
};

#endif