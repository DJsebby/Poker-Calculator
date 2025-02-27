#ifndef DECK_H
#define DECK_H

#include <time.h>

#include <algorithm>
#include <random>
#include <string>
#include <vector>

#include "cards.h"

class deck {
 private:
  std::vector<cards> current_deck;

 public:
  deck() {
    // populate the deck in order

    for (size_t i = 0; i < 13;
         i++)  // loop over the ranks (0 to 12 corresponding to Two to Ace)
    {
      for (size_t j = 0; j < 4; j++)  // loop over the suits
      {
        current_deck.emplace_back(
            static_cast<cards::Rank>(i +
                                     2),  // +2 to align with the correct rank
            static_cast<cards::Suit>(j));
      }
    }

    // now shuffle deck
    shuffleDeck();
  }

  void shuffleDeck() {
    std::random_device s;  // seed from hardware entropy
    std::mt19937 mt(s());
    std::shuffle(current_deck.begin(), current_deck.end(), mt);
    // std::cout << "deck has been shuffled \n";
  }

  cards drawCard() {
    if (current_deck.size() == 0) {
      std::cout << "deck is empty \n";
    }

    cards first_card = current_deck.back();
    current_deck.pop_back();
    return first_card;
  }

  void printDeck() {
    for (size_t i = 0; i < current_deck.size(); i++) {
      std::cout << current_deck[i] << " ";
    }
    std::cout << std::endl;
  }

  std::vector<cards> drawHand() {
    std::vector<cards> hand;
    for (size_t i = 0; i < 2; i++) {
      hand.push_back(drawCard());
    }
    return hand;
  }
  std::vector<cards> drawFullRiver() {
    std::vector<cards> river;
    for (size_t i = 0; i < 5; i++) {
      river.push_back(drawCard());
    }
    return river;
  }

  std::vector<cards> drawFlop() {
    std::vector<cards> flop;
    drawCard();  // to burn the car

    for (size_t i = 0; i < 3; i++) {
      flop.push_back(drawCard());
    }
    return flop;
  }
  cards drawTurn() {
    drawCard();  // to burn the car
    return drawCard();
  }

  cards drawRiver() {
    drawCard();  // to burn the car
    return drawCard();
  }

  void reshuffle(std::vector<cards> cardsR) {
    for (size_t i = 0; i < cardsR.size(); i++) {
      current_deck.push_back(cardsR[i]);
    }

    shuffleDeck();
  }

  int getDeckSize() { return current_deck.size(); }

  // testing functions----------------------------------------------

  std::vector<cards> drawFourHAceC() {  // just for testing purposes
    std::vector<cards> hand;
    for (int i = 0; i < current_deck.size(); i++) {
      if (current_deck[i].getRank() == cards::Rank::Four &&
          current_deck[i].getSuit() == cards::Suit::Hearts) {
        hand.push_back(current_deck[i]);
        current_deck.erase(current_deck.begin() + i);
      }
    }

    for (int i = 0; i < current_deck.size(); i++) {
      if (current_deck[i].getRank() == cards::Rank::Ace &&
          current_deck[i].getSuit() == cards::Suit::Clubs) {
        hand.push_back(current_deck[i]);
        current_deck.erase(current_deck.begin() + i);
      }
    }
    return hand;
  }

  std::vector<cards> drawTenCJackD() {  // just for testing purposes
    std::vector<cards> hand;
    for (int i = 0; i < current_deck.size(); i++) {
      if (current_deck[i].getRank() == cards::Rank::Ten &&
          current_deck[i].getSuit() == cards::Suit::Clubs) {
        hand.push_back(current_deck[i]);
        current_deck.erase(current_deck.begin() + i);
      }
    }

    for (int i = 0; i < current_deck.size(); i++) {
      if (current_deck[i].getRank() == cards::Rank::Jack &&
          current_deck[i].getSuit() == cards::Suit::Diamonds) {
        hand.push_back(current_deck[i]);
        current_deck.erase(current_deck.begin() + i);
      }
    }
    return hand;
  }

  std::vector<cards> drawTestFlop() {
    std::vector<cards> flop;
    // burn card
    current_deck.pop_back();
    // draw 7 of clubs, 10 of heart and 2 of spades
    for (int i = 0; i < current_deck.size(); i++) {
      if (current_deck[i].getRank() == cards::Rank::Seven &&
          current_deck[i].getSuit() == cards::Suit::Clubs) {
        flop.push_back(current_deck[i]);
        current_deck.erase(current_deck.begin() + i);
      }
    }
    for (int i = 0; i < current_deck.size(); i++) {
      if (current_deck[i].getRank() == cards::Rank::Ten &&
          current_deck[i].getSuit() == cards::Suit::Hearts) {
        flop.push_back(current_deck[i]);
        current_deck.erase(current_deck.begin() + i);
      }
    }
    for (int i = 0; i < current_deck.size(); i++) {
      if (current_deck[i].getRank() == cards::Rank::Two &&
          current_deck[i].getSuit() == cards::Suit::Spades) {
        flop.push_back(current_deck[i]);
        current_deck.erase(current_deck.begin() + i);
      }
    }

    return flop;
  }

  cards drawTestTurn() {
    std::vector<cards> Turn;
    // burn card
    current_deck.pop_back();
    // draw Ace of diamonds
    for (int i = 0; i < current_deck.size(); i++) {
      if (current_deck[i].getRank() == cards::Rank::Ace &&
          current_deck[i].getSuit() == cards::Suit::Diamonds) {
        Turn.push_back(current_deck[i]);
        current_deck.erase(current_deck.begin() + i);
      }
    }
    return Turn[0];
  }
  cards drawTestRiver() {
    std::vector<cards> river;
    // burn card
    current_deck.pop_back();
    // draw 2 of diamonds
    for (int i = 0; i < current_deck.size(); i++) {
      if (current_deck[i].getRank() == cards::Rank::Two &&
          current_deck[i].getSuit() == cards::Suit::Diamonds) {
        river.push_back(current_deck[i]);
        current_deck.erase(current_deck.begin() + i);
      }
    }
    return river[0];
  }
};

#endif