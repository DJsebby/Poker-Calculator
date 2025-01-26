#include "winningOdds.h"

int main() {
  deck d;
  std::vector<cards> hand = d.drawHand();
  std::vector<cards> opHand = d.drawHand();
  std::vector<cards> river;
  winningOdds w;

  std::cout << hand[0] << std::endl;
  std::cout << hand[1] << std::endl;

  std::cout << "opponents hand: \n";
  std::cout << opHand[0] << std::endl;
  std::cout << opHand[1] << std::endl;

  w.rawProbabilityOfWinning(hand, opHand, 100000, d);

  std::cout << "100,000 iterations " << std::endl;
  std::cout << w.getOddsOfWinning() << std::endl;

  std::cout << "the flop is: \n\n";

  river = d.drawFlop();

  for (auto card : river) {
    std::cout << card;
  }
  std::cout << "1,000 iterations " << std::endl;
  std::cout << "the probabilty of winning based on the flop is: ";
  w.flopProbabilityOfWinning(hand, river, opHand, 1000, d);
  std::cout << w.getOddsOfWinning() << std::endl;

  return 0;
}