#ifndef W_ODDS_H
#define W_ODDS_H

#include "deck.h"
#include "handEvaluator.h"

class winningOdds {
 private:
  double oddsOfWinning;

 public:
  winningOdds() { oddsOfWinning = 0; }

  double getOddsOfWinning() { return oddsOfWinning; }

  // monte carlo simulator of odds of winning
  void rawProbabilityOfWinning(
      std::vector<cards> &hand, int numOp, int numOfIter,
      deck &d) {  // finds the probability during the first stage of the game
                  // (raw strength)
    double wins = 0;
    double losses = 0;
    double tie = 0;

    handEvaluator a;

    std::vector<std::vector<cards>> opponents;
    opponents.resize(numOp);
    // adding in the opponents

    std::vector<cards> river;
    int maxHandStrength = 0;
    int oppenentHandStrength;
    int heroHandStrength = 0;

    for (size_t i = 0; i < numOfIter; i++) {
      // dealing cards to opponent
      for (int k = 0; k < numOp; k++) {
        for (int j = 0; j < 2; j++) {
          opponents[k].push_back(d.drawCard());
        }
      }
      // dealing river
      river = d.drawFullRiver();

      // find the max opponent strength
      for (int l = 0; l < numOp; l++) {
        oppenentHandStrength = a.evaluateHandStrength(opponents[l], river);
        maxHandStrength = std::max(maxHandStrength, oppenentHandStrength);
      }
      // find hero's hand strength
      heroHandStrength = a.evaluateHandStrength(hand, river);
      // comparing it to the heros hand strength

      if (heroHandStrength == maxHandStrength) {
        tie++;
      } else if (heroHandStrength > maxHandStrength) {
        wins++;
      } else if (heroHandStrength < maxHandStrength) {
        losses++;
      }

      // reset deck for next iteration
      for (int m = 0; m < numOp; m++) {
        d.reshuffle(opponents[m]);
        opponents[m].clear();
      }
      d.reshuffle(river);
      river.clear();
      maxHandStrength = 0;
    }
    // calculate odds of winning
    if ((wins + tie + losses) > 0) {
      oddsOfWinning = (wins + 0.5 * tie) / (wins + tie + losses);
    } else {
      oddsOfWinning = 0;  // Default case for no iterations
    }
  }

  void boardProbabilityOfWinning(std::vector<cards> &hand,
                                 std::vector<cards> &board, int numOp,
                                 int numOfIter, deck &d) {
    double wins = 0;
    double losses = 0;
    double tie = 0;

    handEvaluator a;

    std::vector<cards> currentCards;
    std::vector<std::vector<cards>> opponents;
    opponents.resize(numOp);

    int maxHandStrength = 0;
    int oppenentHandStrength;
    int heroHandStrength = 0;

    for (size_t i = 0; i < numOfIter; i++) {
      // creat board with exisiting cards
      currentCards = board;
      // to complete the board
      for (int p = currentCards.size(); p < 5; p++) {
        currentCards.push_back(d.drawCard());
      }
      // dealing cards to opponent
      for (int k = 0; k < numOp; k++) {
        for (int j = 0; j < 2; j++) {
          opponents[k].push_back(d.drawCard());
        }
      }
      // find the max opponent strength
      for (int l = 0; l < numOp; l++) {
        oppenentHandStrength =
            a.evaluateHandStrength(opponents[l], currentCards);
        maxHandStrength = std::max(maxHandStrength, oppenentHandStrength);
      }
      // find hero's hand strength
      heroHandStrength = a.evaluateHandStrength(hand, currentCards);

      if (heroHandStrength == maxHandStrength) {
        tie++;
      } else if (heroHandStrength > maxHandStrength) {
        wins++;
      } else if (heroHandStrength < maxHandStrength) {
        losses++;
      }

      // reset for the next interation
      for (int m = 0; m < numOp; m++) {
        d.reshuffle(opponents[m]);
        opponents[m].clear();
      }
      // to reshuffle just the new added cards

      d.reshuffle(std::vector<cards>(currentCards.begin() + board.size(),
                                     currentCards.end()));

      currentCards.clear();
      maxHandStrength = 0;
        }

    if ((wins + tie + losses) > 0) {
      oddsOfWinning = (wins + 0.5 * tie) / (wins + tie + losses);
    } else {
      oddsOfWinning = 0;  // Default case for no iterations
    }
  }
};
#endif