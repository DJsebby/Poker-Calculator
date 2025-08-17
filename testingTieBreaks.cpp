#include "handEvaluator.h"

// file to ensure that the hands when tied are being properly evaluted for
// accuracy

int testingStraightTieBreak() {
  std::vector<cards> hand = {{cards::Rank::Four, cards::Suit::Hearts},
                             {cards::Rank::Ace, cards::Suit::Clubs}};
  std::vector<cards> OPhand = {{cards::Rank::Ten, cards::Suit::Clubs},
                               {cards::Rank::Jack, cards::Suit::Diamonds}};

  std::vector<cards> board = {{cards::Rank::King, cards::Suit::Hearts},
                              {cards::Rank::Queen, cards::Suit::Clubs},
                              {cards::Rank::Jack, cards::Suit::Hearts},
                              {cards::Rank::Nine, cards::Suit::Diamonds},
                              {cards::Rank::Ten, cards::Suit::Clubs}};

  handEvaluator h;
  return h.tieBreaker(hand, OPhand, board, 5);
}
int main() {
  std::cout << testingStraightTieBreak() << std::endl;
  return 0;
}