#include "winningOdds.h"

int main() {
  deck d;
  std::vector<cards> hand = d.drawHand();
  std::vector<cards> opHand = d.drawHand();
  std::vector<cards> river = d.drawRiver();

  winningOdds w;

  std::cout << hand[0] << std::endl;
  std::cout << hand[1] << std::endl;

  w.rawProbabilityOfWinning(hand, river, opHand, 100000, d);

  std::cout << "100,000 iterations " << std::endl;
  std::cout << w.getOddsOfWinning() << std::endl;

  
  
  //   std::cout << "1000000 iterations " << std::endl;
  //   std::cout << w.getOddsOfWinning() << std::endl;

  return 0;
}