#include "winningOdds.h"

void runGameSimulation() {
  deck d;
  winningOdds w;
  std::vector<cards> board;

  // first round
  std::vector<cards> hand = d.drawHand();
  std::vector<cards> opHand = d.drawHand();

  std::cout << "your hand: \n";
  std::cout << hand[0] << std::endl;
  std::cout << hand[1] << std::endl;

  std::cout << "opponents hand: \n";
  std::cout << opHand[0] << std::endl;
  std::cout << opHand[1] << std::endl;

  w.rawProbabilityOfWinning(hand, opHand, 100000, d);

  std::cout << "100,000 iterations " << std::endl;
  std::cout << w.getOddsOfWinning() << std::endl;

  // flop
  board = d.drawFlop();

  std::cout << "After the flop the board is: \n\n";
  for (auto card : board) {
    std::cout << card;
  }

  std::cout << "1,000 iterations " << std::endl;
  std::cout << "the probabilty of winning based on the flop is: ";

  w.flopProbabilityOfWinning(hand, board, opHand, 1000, d);
  std::cout << w.getOddsOfWinning() << std::endl;

  // turn
  board.push_back(d.drawTurn());

  std::cout << "AFter the turn the board is: \n\n";
  for (auto card : board) {
    std::cout << card;
  }

  // river (end of the game)
  board.push_back(d.drawRiver());

  std::cout << "AFter the river the board is: \n\n";
  for (auto card : board) {
    std::cout << card;
  }
  std::cout << "The final probability of winning is: \n";
}

int main() {
  runGameSimulation();
  return 0;
}