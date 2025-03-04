
#include "test.h"

#include <set>

double testGetProbability(
    std::vector<cards> &hand, std::vector<cards> &OPhand,
    std::vector<cards> board, int numOp, int numOfIter,
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

  std::unordered_set<int> resChecker;
  for (int i = 0; i < numOfIter; i++) {
    // create board with exisiting cards
    currentCards = board;
    // to complete the board
    for (int p = currentCards.size(); p < 5; p++) {
      currentCards.push_back(d.drawCard());
    }

    // find hero's hand strength
    heroHandStrength = a.evaluateHandStrength(hand, currentCards);

    // find opponent hand strength
    oppenentHandStrength = a.evaluateHandStrength(OPhand, currentCards);

    // std::cout << "Hero Strength: " << heroHandStrength
    //           << ", Opponent Strength: " << oppenentHandStrength <<
    //           std::endl;

    resChecker.insert(oppenentHandStrength);
    resChecker.insert(heroHandStrength);

    // std::cout << "unique cards: " << resChecker.size() << std::endl;

    if (i % 1000 == 0) {
      std::cout << "Unique hand strengths so far: " << resChecker.size()
                << std::endl;
    }

    // for (size_t g = 0; g < currentCards.size(); g++) {
    //   std::cout << currentCards[g];
    // }

    // if (heroHandStrength >= 9) {
    //   std::cout << "Detected strong hand: " << heroHandStrength << std::endl;
    // }

    if (heroHandStrength == oppenentHandStrength) {
      int res = a.tieBreaker(hand, OPhand, currentCards, heroHandStrength);

      switch (res) {
        case 1:
          wins++;
          break;
        case 0:
          losses++;
          break;
        case -1:
          // std::cout << "there was a tie and the community cards are: \n";
          // for (size_t i = 0; i < currentCards.size(); i++) {
          //   std::cout << currentCards[i];
          // }
          // std::cout << "the hand score is " << heroHandStrength << std::endl;
          tie++;
          break;
        default:
          std::cout << "deafult condition for tie breaker called" << res
                    << std::endl;
          break;
      }
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

double testingTheFlop(std::vector<cards> &hand, std::vector<cards> &OPhand,
                      int numOfIter) {
  double oddsOfWinning = 0;
  double wins = 0;
  double losses = 0;
  double tie = 0;

  deck d;
  handEvaluator a;

  std::vector<cards> currentCards;

  int oppenentHandStrength = 0;
  int heroHandStrength = 0;

  std::vector<cards> burntCards;

  for (int i = 0; i < numOfIter; i++) {
    currentCards = d.drawTestFlop2();
    burntCards.push_back(d.drawCard());
    for (size_t k = currentCards.size(); k < 5; k++) {
      burntCards.push_back(d.drawCard());
      currentCards.push_back(d.drawCard());
    }

    // find hero's hand strength
    heroHandStrength = a.evaluateHandStrength(hand, currentCards);

    // find opponent hand strength
    oppenentHandStrength = a.evaluateHandStrength(OPhand, currentCards);

    if (heroHandStrength >= 9) {
      std::cout << "Detected strong hand: " << heroHandStrength << std::endl;
    }

    if (heroHandStrength == oppenentHandStrength) {
      int res = a.tieBreaker(hand, OPhand, currentCards, heroHandStrength);
      switch (res) {
        case 1:
          wins++;
          break;
        case 0:
          losses++;
          break;
        case -1:
          tie++;
          break;
        default:
          std::cout << "deafult condition for tie breaker called" << res
                    << std::endl;
          break;
      }
    } else if (heroHandStrength > oppenentHandStrength) {
      wins++;
    } else if (heroHandStrength < oppenentHandStrength) {
      losses++;
    }

    // to reshuffle just the new added cards

    d.reshuffle(std::vector<cards>(currentCards.begin(), currentCards.end()));
    d.reshuffle(std::vector<cards>(burntCards.begin(), burntCards.end()));
    currentCards.clear();
    burntCards.clear();
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
  std::cout << hand[0];
  std::cout << hand[1];

  std::cout << "opponent hand: \n";
  std::vector<cards> OPhand = d.drawTenCJackD();

  std::cout << OPhand[0];
  std::cout << OPhand[1];

  std::cout << "1 ---  " << std::endl;
  std::cout << "the raw probability is (54.81) "
            << testGetProbability(hand, OPhand, board, numberOP, 1000, d)
            << std::endl;

  // flop
  board = d.drawTestFlop();

  std::cout << "2 --- After the flop the board is: \n\n";
  for (auto card : board) {
    std::cout << card;
  }

  std::cout << "online is: 13.43 \n";
  std::cout << "we get: ";

  std::cout << testingTheFlop(hand, OPhand, 100000) << std::endl;

  board.push_back(d.drawTestTurn());

  std::cout << "3 --- After the turn the board is: \n\n";
  for (auto card : board) {
    std::cout << card;
  }

  std::cout << "online is: 88.64 \n";
  std::cout << "we get: ";

  std::cout << testGetProbability(hand, OPhand, board, numberOP, 1000, d)
            << std::endl;
  board.push_back(d.drawTestRiver());

  std::cout << "4 --- After the river the board is: \n\n";
  for (auto card : board) {
    std::cout << card;
  }

  std::cout << "The probability of winning the gane is: \n";

  std::cout << testGetProbability(hand, OPhand, board, numberOP, 10, d)
            << std::endl;
}
