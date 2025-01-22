#include "winningOdds.h"

int main() {
  deck d;
  std::vector<cards> hand = d.drawHand();
  std::vector<cards> opHand = d.drawHand();
  std::vector<cards> river = d.drawRiver();

  winningOdds w;

  std::cout << hand[0] << std::endl;
  std::cout << hand[1] << std::endl;

  //    w.oddsOfWinning(hand, river, opHand, 10000, d);
  w.SimProbabilityOfWinning(hand, river, opHand, 10, d);

  std::cout << w.getOddsOfWinning();

  return 0;
}