#include "handEvaluator.h"

// file to ensure that the hands are being properly evaluted for accuracy

int testRoyalFlush() {
  std::vector<cards> hand = {{cards::Rank::Ace, cards::Suit::Clubs},
                             {cards::Rank::Jack, cards::Suit::Clubs}};

  std::vector<cards> board = {{cards::Rank::King, cards::Suit::Hearts},
                              {cards::Rank::Ace, cards::Suit::Clubs},
                              {cards::Rank::Seven, cards::Suit::Hearts},
                              {cards::Rank::Queen, cards::Suit::Clubs},
                              {cards::Rank::Ten, cards::Suit::Clubs}};

  handEvaluator h;
  return h.evaluateHandStrength(hand, board);
}

int testStraightFlush() {
  std::vector<cards> hand = {{cards::Rank::Six, cards::Suit::Clubs},
                             {cards::Rank::Five, cards::Suit::Clubs}};

  std::vector<cards> board = {{cards::Rank::King, cards::Suit::Hearts},
                              {cards::Rank::Seven, cards::Suit::Clubs},
                              {cards::Rank::Eight, cards::Suit::Hearts},
                              {cards::Rank::Nine, cards::Suit::Clubs},
                              {cards::Rank::Ten, cards::Suit::Clubs}};

  handEvaluator h;
  return h.evaluateHandStrength(hand, board);
}

int testFourOfaKind() {
  std::vector<cards> hand = {{cards::Rank::Five, cards::Suit::Hearts},
                             {cards::Rank::Five, cards::Suit::Clubs}};

  std::vector<cards> board = {{cards::Rank::Five, cards::Suit::Diamonds},
                              {cards::Rank::Seven, cards::Suit::Clubs},
                              {cards::Rank::Eight, cards::Suit::Hearts},
                              {cards::Rank::Five, cards::Suit::Spades},
                              {cards::Rank::Ten, cards::Suit::Clubs}};

  handEvaluator h;
  return h.evaluateHandStrength(hand, board);
}

int testFullHouse() {
  std::vector<cards> hand = {{cards::Rank::Five, cards::Suit::Hearts},
                             {cards::Rank::Five, cards::Suit::Clubs}};

  std::vector<cards> board = {{cards::Rank::Five, cards::Suit::Diamonds},
                              {cards::Rank::Seven, cards::Suit::Clubs},
                              {cards::Rank::Eight, cards::Suit::Hearts},
                              {cards::Rank::Seven, cards::Suit::Spades},
                              {cards::Rank::Ten, cards::Suit::Clubs}};

  handEvaluator h;
  return h.evaluateHandStrength(hand, board);
}

int testFlush() {
  std::vector<cards> hand = {{cards::Rank::Five, cards::Suit::Hearts},
                             {cards::Rank::Two, cards::Suit::Hearts}};

  std::vector<cards> board = {{cards::Rank::Five, cards::Suit::Hearts},
                              {cards::Rank::Seven, cards::Suit::Hearts},
                              {cards::Rank::Eight, cards::Suit::Hearts},
                              {cards::Rank::Seven, cards::Suit::Spades},
                              {cards::Rank::Ten, cards::Suit::Clubs}};

  handEvaluator h;
  return h.evaluateHandStrength(hand, board);
}

int testStraight() {
  std::vector<cards> hand = {{cards::Rank::Five, cards::Suit::Hearts},
                             {cards::Rank::Two, cards::Suit::Hearts}};

  std::vector<cards> board = {{cards::Rank::Three, cards::Suit::Diamonds},
                              {cards::Rank::Six, cards::Suit::Hearts},
                              {cards::Rank::Eight, cards::Suit::Hearts},
                              {cards::Rank::Four, cards::Suit::Spades},
                              {cards::Rank::Ten, cards::Suit::Clubs}};

  handEvaluator h;
  return h.evaluateHandStrength(hand, board);
}

int test3ofaKind() {
  std::vector<cards> hand = {{cards::Rank::Ace, cards::Suit::Diamonds},
                             {cards::Rank::Ten, cards::Suit::Hearts}};

  std::vector<cards> board = {{cards::Rank::Ace, cards::Suit::Hearts},
                              {cards::Rank::Ace, cards::Suit::Clubs},
                              {cards::Rank::Seven, cards::Suit::Hearts},
                              {cards::Rank::Four, cards::Suit::Clubs},
                              {cards::Rank::Two, cards::Suit::Clubs}};
  handEvaluator h;
  return h.evaluateHandStrength(hand, board);
}

int testTwoPair() {
  std::vector<cards> hand = {{cards::Rank::Ace, cards::Suit::Diamonds},
                             {cards::Rank::Ten, cards::Suit::Hearts}};

  std::vector<cards> board = {{cards::Rank::Ten, cards::Suit::Hearts},
                              {cards::Rank::Ace, cards::Suit::Clubs},
                              {cards::Rank::Seven, cards::Suit::Hearts},
                              {cards::Rank::Four, cards::Suit::Clubs},
                              {cards::Rank::Two, cards::Suit::Clubs}};
  handEvaluator h;
  return h.evaluateHandStrength(hand, board);
}

int testPair() {
  std::vector<cards> hand = {{cards::Rank::Ace, cards::Suit::Diamonds},
                             {cards::Rank::Ten, cards::Suit::Hearts}};

  std::vector<cards> board = {{cards::Rank::Nine, cards::Suit::Hearts},
                              {cards::Rank::Ace, cards::Suit::Clubs},
                              {cards::Rank::Seven, cards::Suit::Hearts},
                              {cards::Rank::Four, cards::Suit::Clubs},
                              {cards::Rank::Two, cards::Suit::Clubs}};
  handEvaluator h;
  return h.evaluateHandStrength(hand, board);
}

int testHighCard() {
  std::vector<cards> hand = {{cards::Rank::Ace, cards::Suit::Diamonds},
                             {cards::Rank::Ten, cards::Suit::Hearts}};

  std::vector<cards> board = {{cards::Rank::Nine, cards::Suit::Hearts},
                              {cards::Rank::Three, cards::Suit::Clubs},
                              {cards::Rank::Seven, cards::Suit::Hearts},
                              {cards::Rank::Four, cards::Suit::Clubs},
                              {cards::Rank::Two, cards::Suit::Clubs}};
  handEvaluator h;
  return h.evaluateHandStrength(hand, board);
}

int main() {
  std::cout << testHighCard() << std::endl;
  return 0;
}