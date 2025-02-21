#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

class cards {
 public:
  enum class Suit { Hearts, Diamonds, Clubs, Spades };
  enum class Rank {
    Two = 2,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace
  };
  cards(Rank a, Suit b) : rank(a), suit(b) {}
  Rank getRank() const { return rank; }
  Suit getSuit() const { return suit; }

  friend std::ostream& operator<<(std::ostream& os, const cards& card) {
    return os << "rank: " << card.rankToString()
              << ", suit: " << card.suitToString() << std::endl;
  }

  std::string rankToString() const {
    switch (rank) {
      case Rank::Two:
        return "Two";
      case Rank::Three:
        return "Three";
      case Rank::Four:
        return "Four";
      case Rank::Five:
        return "Five";
      case Rank::Six:
        return "Six";
      case Rank::Seven:
        return "Seven";
      case Rank::Eight:
        return "Eight";
      case Rank::Nine:
        return "Nine";
      case Rank::Ten:
        return "Ten";
      case Rank::Jack:
        return "Jack";
      case Rank::Queen:
        return "Queen";
      case Rank::King:
        return "King";
      case Rank::Ace:
        return "Ace";
      default:
        return "Unknown";
    }
  }

  std::string suitToString() const {
    switch (suit) {
      case Suit::Hearts:
        return "Hearts";
      case Suit::Diamonds:
        return "Diamonds";
      case Suit::Clubs:
        return "Clubs";
      case Suit::Spades:
        return "Spades";
      default:
        return "Unknown";
    }
  }

  int getRankAsInt() const { return static_cast<int>(rank); }

 private:
  Rank rank;
  Suit suit;
};

namespace std {
template <>
struct hash<cards> {
  size_t operator()(const cards& card) const {
    size_t rankHash = std::hash<int>()(static_cast<int>(card.getRank()));
    size_t suitHash = std::hash<int>()(static_cast<int>(card.getSuit()));

    return rankHash ^ (suitHash << 1);
  }
};
}  // namespace std

#endif
