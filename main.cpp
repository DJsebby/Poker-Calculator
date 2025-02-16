#include "test.cpp"
#include "winningOdds.h"

void runGameSimulation(int numOp) {
  deck d;
  winningOdds w;
  std::vector<cards> board;

  int numberOP = numOp;

  // first round
  std::vector<cards> hand = d.drawHand();

  std::cout << "your hand: \n";
  std::cout << hand[0] << std::endl;
  std::cout << hand[1] << std::endl;

  w.rawProbabilityOfWinning(hand, numberOP, 100000, d);

  std::cout << "100,000 iterations " << std::endl;
  std::cout << w.getOddsOfWinning() << std::endl;

  // flop
  board = d.drawFlop();

  std::cout << "After the flop the board is: \n\n";
  for (auto card : board) {
    std::cout << card;
  }

  std::cout << "100,000 iterations " << std::endl;
  std::cout << "the probabilty of winning based on the flop is: ";

  w.boardProbabilityOfWinning(hand, board, numberOP, 100000, d);
  std::cout << w.getOddsOfWinning() << std::endl;

  // turn
  board.push_back(d.drawTurn());

  std::cout << "AFter the turn the board is: \n\n";
  for (auto card : board) {
    std::cout << card;
  }

  std::cout << "100,000 iterations " << std::endl;
  std::cout << "the probabilty of winning based on the flop is: ";

  w.boardProbabilityOfWinning(hand, board, numberOP, 100000, d);
  std::cout << w.getOddsOfWinning() << std::endl;

  // river (end of the game)
  board.push_back(d.drawRiver());

  std::cout << "After the river the board is: \n\n";
  for (auto card : board) {
    std::cout << card;
  }

  std::cout << "100,000 iterations " << std::endl;
  std::cout << "The final probability of winning is: \n";

  w.boardProbabilityOfWinning(hand, board, numberOP, 100000, d);
  std::cout << w.getOddsOfWinning() << std::endl;
}

int main() {
  // runGameSimulation(1);
  oneOpponentSetCards();
  return 0;
}