
#include "test.h"

double testGetProbability(
    std::vector<cards> &hand, std::vector<cards> &OPhand,
    std::vector<cards> &board, int numOp, int numOfIter,
    deck &d) {  // a testing function that doesnt modify the opponent hand but
                // is a copy of the implement probability caclutor
  double oddsOfWinning = 0;
  double wins = 0;
  double losses = 0;
  double tie = 0;

  handEvaluator a;

  std::vector<cards> currentCards;
  std::vector<std::vector<cards>> opponents;
  opponents.resize(numOp);

  int oppenentHandStrength = 0;
  int heroHandStrength = 0;

  for (size_t i = 0; i < numOfIter; i++) {
    // creat board with exisiting cards
    currentCards = board;
    // to complete the board
    for (int p = currentCards.size(); p < 5; p++) {
      currentCards.push_back(d.drawCard());
    }

    // find hero's hand strength
    heroHandStrength = a.evaluateHandStrength(hand, currentCards);
    // find opponent hand strength
    oppenentHandStrength = a.evaluateHandStrength(OPhand, currentCards);

    if (heroHandStrength == oppenentHandStrength) {
      tie++;
    } else if (heroHandStrength > oppenentHandStrength) {
      wins++;
    } else if (heroHandStrength < oppenentHandStrength) {
      losses++;
    }

    // to reshuffle just the new added cards

    d.reshuffle(std::vector<cards>(currentCards.begin() + board.size(),
                                   currentCards.end()));

    currentCards.clear();
  }

  if ((wins + tie + losses) > 0) {
    oddsOfWinning = (wins + 0.5 * tie) / (wins + tie + losses);
  } else {
    oddsOfWinning = 0;  // Default case for no iterations
  }
  return oddsOfWinning;
}

void oneOpponentSetCards() {
  deck d;
  winningOdds w;
  std::vector<cards> board;

  int numberOP = 1;

  // first round
  std::vector<cards> hand = d.drawFourHAceC();

  std::cout << "your hand: \n";
  std::cout << hand[0] << std::endl;
  std::cout << hand[1] << std::endl;

  std::cout << "opponent hand: \n";
  std::vector<cards> OPhand = d.drawTenCJackD();

  std::cout << OPhand[0] << std::endl;
  std::cout << OPhand[1] << std::endl;

  std::cout << "1 ---  " << std::endl;
  std::cout << "the raw probability is"
            << testGetProbability(hand, OPhand, board, numberOP, 100000, d)
            << std::endl;

  // flop
  board = d.drawTestFlop();

  std::cout << "2 --- After the flop the board is: \n\n";
  for (auto card : board) {
    std::cout << card;
  }

  std::cout << "The probability of winning based on these cards is: \n";

  std::cout << testGetProbability(hand, OPhand, board, numberOP, 100000, d)
            << std::endl;

  board.push_back(d.drawTestTurn());

  std::cout << "3 --- After the turn the board is: \n\n";
  for (auto card : board) {
    std::cout << card;
  }

  std::cout << "The probability of winning based on these cards is: \n";

  std::cout << testGetProbability(hand, OPhand, board, numberOP, 100000, d)
            << std::endl;
  board.push_back(d.drawTestRiver());

  std::cout << "4 --- After the river the board is: \n\n";
  for (auto card : board) {
    std::cout << card;
  }

  std::cout << "The probability of winning the gane is: \n";

  std::cout << testGetProbability(hand, OPhand, board, numberOP, 100000, d)
            << std::endl;
}
