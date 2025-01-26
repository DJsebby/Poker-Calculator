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
  void rawProbabilityOfWinning(std::vector<cards> &hand,
                               std::vector<cards> &opHand, int numOfIter,
                               deck &d) {
    float wins = 0;
    float losses = 0;
    float tie = 0;

    handEvaluator a;

    std::vector<cards> river = d.drawRiver();

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

  void flopProbabilityOfWinning(
      std::vector<cards> &hand, std::vector<cards> &flop,
      std::vector<cards> &opHand, int numOfIter,
      deck &d) {  //<--- need to re-write the logic for how the game plays, raw
                  // logic is fine but once the flop comes we need to keep them
                  // the same but check the prob of the other 2 and op hand
    float wins = 0;
    float losses = 0;
    float tie = 0;

    handEvaluator a;

    std::vector<cards> river = flop;
    std::vector<cards> twoExtra;

    // river is equal to the flop + 2 additional cards
    for (int i = 0; i < 2; i++) {
      river.push_back(d.drawCard());
    }

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

      twoExtra.push_back(river.back());
      river.pop_back();
      twoExtra.push_back(river.back());
      river.pop_back();
      d.reshuffle(opHand, twoExtra);
      opHand.clear();
      opHand = d.drawHand();

      for (int i = 0; i < 2; i++) {
        river.push_back(d.drawCard());
      }
    }

    if ((wins + tie + losses) > 0) {
      oddsOfWinning = (wins + 0.5 * tie) / (wins + tie + losses);
    } else {
      oddsOfWinning = 0;  // Default case for no iterations
    }
  }
};
#endif